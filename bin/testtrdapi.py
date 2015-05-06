__author__ = 'yanghua'

import tdapi
import mdapi
import os
import userapidef
import time
import copy


global md_api
global trd_api
global md_active
global my_request_id
global order_ref
global orders

md_api = None
trd_api = None
md_active = False
my_request_id = 0
order_ref = 0
orders = {}


class MyMdSpi(mdapi.MarketDataSpi):
    def __init__(self, api, instruments, exchange, broker_id, investor_id, password):
        self._api = api
        self._exchange = exchange
        self._request_id = 0
        self._instruments = instruments
        self._broker_id = broker_id
        self._investor_id = investor_id
        self._password = password

        #self._orders = {}

    def on_front_connected(self):
        self._request_id += 1

        param = {'BrokerID': self._broker_id, 'UserID': self._investor_id, 'Password': self._password}
        self._api.req_user_login(param, self._request_id)
        global md_active
        md_active = True

    def on_front_disconnected(self, reason, message):
        print("disconnected", message)
        global md_active
        md_active = False

    def on_rsp_user_login(self, rsp_user_login, rsp_err_id, rsp_err_msg, request_id, is_last):
        print(
            self.__class__.__name__, tdapi.get_current_function_name(), rsp_user_login, rsp_err_id, rsp_err_msg,
            request_id,
            is_last)
        print("login", self._api.get_trading_day())
        print(self._api.subscribe_market_data(self._instruments))

    def on_rsp_user_logout(self, user_logout, rsp_err_id, rsp_err_msg, request_id, is_last):
        print("logout", user_logout, rsp_err_id, rsp_err_msg, request_id, is_last)

    def on_rsp_error(self, rsp_err_id, rsp_err_msg, request_id, is_last):
        print("error", rsp_err_id, rsp_err_msg, request_id, is_last)

    def on_rsp_sub_market_data(self, specific_instrument, rsp_err_id, rsp_err_msg, request_id, is_last):
        #print(rsp_err_msg.decode('GBK'))
        #print("sub_market_data", specific_instrument, rsp_err_id, rsp_err_msg, request_id, is_last)
        pass

    def on_rsp_unsub_market_data(self, specific_instrument, rsp_err_id, rsp_err_msg, request_id, is_last):
        print(rsp_err_msg)
        print("unsub_market_data", specific_instrument, rsp_err_id, rsp_err_msg, request_id, is_last)
        pass

    def on_rtn_depth_market_data(self, depth_market_data):
        global orders
        if '11000071' != depth_market_data['InstrumentID']:
            print(depth_market_data)

            if len(orders) == 0:
                ord_ref = MyTrdSpi.get_next_ord_ref()
                param = {'BrokerID': self._broker_id, 'InvestorID': self._investor_id,
                         'InstrumentID': depth_market_data['InstrumentID'],
                         'UserID': self._investor_id, 'OrderRef': ord_ref,
                         'OrderPriceType': userapidef.KS_OTP_OPT_LimitPrice,
                         'Direction': userapidef.KS_OTP_D_Buy, 'OffsetFlag': userapidef.KS_OTP_OF_Open,
                         'HedgeFlag': userapidef.KS_OTP_HF_Speculation, 'LimitPrice': depth_market_data['BidPrice5'],
                         'VolumeTotalOriginal': 1,
                         'TimeCondition': userapidef.KS_OTP_TC_GFD, 'VolumeCondition': userapidef.KS_OTP_VC_AV,
                         'MinVolume': 0, 'ContingentCondition': userapidef.KS_OTP_CC_Immediately, 'StopPrice': 0,
                         'RequestID': MyTrdSpi.get_next_id()}

                if trd_api.req_order_insert(param, param['RequestID']) == 0:
                    orders[ord_ref] = param
                    print '->>>>>>>', orders
            else:
                for ref in orders:
                    param = orders[ref]
                    pms = {'BrokerID': self._broker_id, 'InvestorID': self._investor_id}
                    trd_api.req_qry_order(pms, MyTrdSpi.get_next_id())


class MyTrdSpi(tdapi.TradeSpi):
    def __init__(self, api, instruments, exchange, broker_id, investor_id, password):
        self._api = api
        self._exchange = exchange
        self._instruments = []
        self._broker_id = broker_id
        self._investor_id = investor_id
        self._password = password
        self._isOk = False
        self._inst_info = {}
        self._qry_inst_ok = False

    @staticmethod
    def get_next_id():
        global my_request_id
        my_request_id += 1
        return my_request_id

    @staticmethod
    def get_next_ord_ref():
        global order_ref
        order_ref += 1
        return str(order_ref)

    def on_front_connected(self):
        param = {'BrokerID': self._broker_id, 'UserID': self._investor_id, 'Password': self._password}
        self._api.req_user_login(param, self.get_next_id())

    def on_front_disconnected(self, reason, message):
        print("disconnected", message)
        self._isOk = False

    def on_rsp_user_login(self, rsp_user_login, rsp_err_id, rsp_err_msg, request_id, is_last):
        if not is_last:
            return
        print(
            self.__class__.__name__, tdapi.get_current_function_name(), rsp_user_login, rsp_err_id, rsp_err_msg,
            request_id,
            is_last)
        print(rsp_err_msg.decode('GBK'))
        # print("login", self._api.get_trading_day())
        # print(rsp_user_login['SystemName'].decode('GBK'))
        self._api.subscribe_private_topic(userapidef.KS_OTP_TERT_RESUME)
        self._api.subscribe_public_topic(userapidef.KS_OTP_TERT_RESUME)

        param = {'BrokerID': self._broker_id, 'InvestorID': self._investor_id}
        print self._api.req_settlement_info_confirm(param, self.get_next_id())

        param = {'BrokerID': self._broker_id, 'InvestorID': self._investor_id}
        print self._api.req_qry_trading_account(param, self.get_next_id())

        param = {'BrokerID': self._broker_id, 'InvestorID': self._investor_id}
        print self._api.req_qry_investor(param, self.get_next_id())

        param = {'ExchangeID': self._exchange}
        print self._api.req_qry_instrument(param, self.get_next_id())

        param = {'BrokerID': self._broker_id, 'InvestorID': self._investor_id}
        print self._api.req_qry_investor_position(param, self.get_next_id())

        param = {'BrokerID': self._broker_id, 'InvestorID': self._investor_id}
        print self._api.req_qry_investor_position_detail(param, self.get_next_id())

    def on_rsp_order_insert(self, input_order, rsp_err_id, rsp_err_msg, request_id, is_last):
        print(rsp_err_msg.decode('GBK'))
        print(
            self.__class__.__name__, tdapi.get_current_function_name(), input_order, rsp_err_id,
            rsp_err_msg, request_id, is_last)

    def on_rtn_order(self, order):
        print(self.__class__.__name__, tdapi.get_current_function_name(), order)

    def on_rtn_trade(self, trade):
        print(self.__class__.__name__, tdapi.get_current_function_name(), trade)

    def on_rsp_qry_instrument(self, instrument, rsp_err_id, rsp_err_msg, request_id, is_last):
        print(
            self.__class__.__name__, tdapi.get_current_function_name(), instrument, rsp_err_id, rsp_err_msg, request_id,
            is_last)

        inst_id = instrument['InstrumentID']

        if inst_id in self._inst_info:
            self._inst_info[inst_id][0] = instrument
        else:
            self._inst_info[inst_id] = [copy.copy(instrument), None, None]

        param = {'BrokerID': self._broker_id, 'InstrumentID': instrument['InstrumentID'],
                 'InvestorID': self._investor_id, 'ExchangeID': instrument['ExchangeID']}
        self._api.req_qry_otp_ins_comm_rate(param, self.get_next_id())

        param['HedgeFlag'] = userapidef.KS_OTP_CIDT_UnCovered
        self._api.req_qry_otp_ins_margin_rate(param, self.get_next_id())

        self._instruments.append(instrument['InstrumentID'])
        self._qry_inst_ok = is_last
        self._isOk = is_last

    def on_rsp_qry_instrument_margin_rate(self, instrument_margin_rate, rsp_err_id, rsp_err_msg, request_id,
                                          is_last):
        if 'InstrumentID' not in instrument_margin_rate:
            return
        inst_id = instrument_margin_rate['InstrumentID']
        if inst_id in self._inst_info:
            self._inst_info[inst_id][1] = copy.copy(instrument_margin_rate)

        self._isOk = self.check_service_ok()

    def on_rsp_qry_otp_ins_comm_rate(self, otp_ins_comm_rate, rsp_err_id, rsp_err_msg, request_id, is_last):
        if 'InstrumentID' not in otp_ins_comm_rate:
            return
        inst_id = otp_ins_comm_rate['InstrumentID']
        if inst_id in self._inst_info:
            self._inst_info[inst_id][2] = copy.copy(otp_ins_comm_rate)

        self._isOk = self.check_service_ok()

    def check_service_ok(self):
        if not self._qry_inst_ok:
            return False

        for k in self._inst_info:
            item = self._inst_info[k]
            if (item[0] is None) or (item[1] is None) or (item[2] is None):
                return False

        return True

    def is_service_ok(self):
        return self._isOk

    def get_all_instruments(self):
        return self._instruments

    def get_inst_info(self):
        return self._inst_info

    def on_rsp_qry_order(self, order, rsp_err_id, rsp_err_msg, request_id, is_last):
        global orders

        if len(order) > 0:
            #order['VolumeTotalOriginal'] =  order['VolumeTraded']
            if order['OrderSysID'] != 0:
                print(
                    self.__class__.__name__, tdapi.get_current_function_name(), order, rsp_err_id, rsp_err_msg, request_id, is_last)
                param = {'BrokerID': self._broker_id, 'InvestorID': self._investor_id, 'OrderRef': order['OrderRef'],
                         'FrontID': order['FrontID'], 'SessionID': order['SessionID'],
                         'ExchangeID': order['ExchangeID'],
                         'OrderSysID': order['OrderSysID']}
                print(self._api.req_order_action(param, self.get_next_id()))
            if order['OrderStatus'] in (userapidef.KS_OTP_OST_Canceled, userapidef.KS_OTP_OST_AllTraded):
                orders.clear()


def run():
    try:
        path = os.getcwd()
        # initial market data
        global md_api, trd_api

        trd_api = tdapi.TradeApi.create_api(os.path.join(path, "log"))
        spi = MyTrdSpi(trd_api, instruments=['11000071', '11000076'],
                       exchange='SSE',
                       broker_id="31000853",
                       investor_id="20420418",
                       password="123456")
        trd_api.register_spi(spi)
        trd_api.register_front("tcp://116.236.247.173:17996")
        trd_api.init()

        c = 10
        while not spi.is_service_ok():
            time.sleep(1)
            c -= 1
            if c <= 0:
                break
            print('Waiting for trading service up...')

        # print(spi.get_all_instruments())
        insts = spi.get_inst_info()
        for key in insts:
            inst = insts[key][0]
            margin = insts[key][1]
            cmmm = insts[key][2]
            if margin is not None:
                print(margin)

        md_api = mdapi.MarketDataApi.create_api(os.path.join(path, "log"))
        spi2 = MyMdSpi(md_api, instruments=spi.get_all_instruments(),
                       exchange='SSE',
                       broker_id="31000853",
                       investor_id="20420418",
                       password="123456")
        md_api.register_spi(spi2)
        md_api.register_front("tcp://116.236.247.173:17996")
        md_api.init()

        os.system("pause")
        trd_api.release()
        md_api.release()
    except Exception as err:
        print(err)


run()