__author__ = 'yanghua'

import tdapi
import mdapi
import os
import userapidef

global md_api
global trd_api


class MyMdSpi(mdapi.MarketDataSpi):
    def __init__(self, api, instruments, exchange, broker_id, investor_id, password):
        self._api = api
        self._exchange = exchange
        self._request_id = 0
        self._instruments = instruments
        self._broker_id = broker_id
        self._investor_id = investor_id
        self._password = password

    def on_front_connected(self):
        self._request_id += 1

        param = {'BrokerID': self._broker_id, 'UserID': self._investor_id, 'Password': self._password}
        self._api.req_user_login(param, self._request_id)

    def on_front_disconnected(self, reason, message):
        print("disconnected", message)

    def on_rsp_user_login(self, rsp_user_login, rsp_err_id, rsp_err_msg, request_id, is_last):
        print("login", rsp_user_login, rsp_err_id, rsp_err_msg, request_id, is_last)
        print("login", self._api.get_trading_day())
        print(rsp_user_login['SystemName'].decode('GBK'))
        print(self._api.subscribe_market_data(self._instruments))

    def on_rsp_user_logout(self, user_logout, rsp_err_id, rsp_err_msg, request_id, is_last):
        print("logout", user_logout, rsp_err_id, rsp_err_msg, request_id, is_last)

    def on_rsp_error(self, rsp_err_id, rsp_err_msg, request_id, is_last):
        print("error", rsp_err_id, rsp_err_msg.decode('GBK'), request_id, is_last)

    def on_rsp_sub_market_data(self, specific_instrument, rsp_err_id, rsp_err_msg, request_id, is_last):
        print("sub_market_data", specific_instrument, rsp_err_id, rsp_err_msg, request_id, is_last)

    def on_rsp_unsub_market_data(self, specific_instrument, rsp_err_id, rsp_err_msg, request_id, is_last):
        print("unsub_market_data", specific_instrument, rsp_err_id, rsp_err_msg, request_id, is_last)

    def on_rtn_depth_market_data(self, depth_market_data):
        print(depth_market_data)


class MyTrdSpi(tdapi.TradeSpi):
    def __init__(self, api, instruments, exchange, broker_id, investor_id, password):
        self._api = api
        self._exchange = exchange
        self._request_id = 0
        self._instruments = instruments
        self._broker_id = broker_id
        self._investor_id = investor_id
        self._password = password

    def on_front_connected(self):
        self._request_id += 1
        param = {'BrokerID': self._broker_id, 'UserID': self._investor_id, 'Password': self._password}
        self._api.req_user_login(param, self._request_id)

    def on_front_disconnected(self, reason, message):
        print("disconnected", message)

    def on_rsp_user_login(self, rsp_user_login, rsp_err_id, rsp_err_msg, request_id, is_last):
        print("login", rsp_user_login, rsp_err_id, rsp_err_msg, request_id, is_last)
        print("login", self._api.get_trading_day())
        # print(rsp_user_login['SystemName'].decode('GBK'))
        self._api.subscribe_private_topic(userapidef.KS_OTP_TERT_RESUME)
        self._api.subscribe_public_topic(userapidef.KS_OTP_TERT_RESUME)

        param = {'BrokerID': self._broker_id, 'InvestorID': self._investor_id}
        self._request_id += 1
        self._api.req_qry_trading_account(param, self._request_id)

        param = {'BrokerID': self._broker_id, 'InvestorID': self._investor_id}
        self._request_id += 1
        self._api.req_qry_investor(param, self._request_id)

        param = {'ExchangeID': self._exchange}
        self._request_id += 1
        self._api.req_qry_instrument(param, self._request_id)

        for inst in self._instruments:
            param = {'BrokerID': self._broker_id, 'InstrumentID': inst, 'InvestorID': self._investor_id,
                     'ExchangeID': self._exchange}
            self._request_id += 1
            self._api.req_qry_otp_ins_comm_rate(param, self._request_id)

            param[''] = userapidef.KS_OTP_CIDT_UnCovered
            self._request_id += 1
            self._api.req_qry_otp_ins_margin_rate(param, self._request_id)

        param = {'BrokerID': self._broker_id, 'InvestorID': self._investor_id}
        self._request_id += 1
        self._api.req_qry_investor_position(param, self._request_id)

        param = {'BrokerID': self._broker_id, 'InvestorID': self._investor_id}
        self._request_id += 1
        self._api.req_qry_investor_position_detail(param, self._request_id)

        param = {'BrokerID': self._broker_id, 'InvestorID': self._investor_id, 'ConfirmDate': ''}
        self._request_id += 1
        self._api.req_settlement_info_confirm(param, self._request_id)

        self._request_id += 1
        param = {'BrokerID': self._broker_id, 'InvestorID': self._investor_id, 'InstrumentID': '11000071',
                 'UserID': self._investor_id, 'OrderRef': 1, 'OrderPriceType': userapidef.KS_OTP_OPT_LimitPrice,
                 'Direction': userapidef.KS_OTP_D_Buy, 'OffsetFlag': userapidef.KS_OTP_OF_Open,
                 'HedgeFlag': userapidef.KS_OTP_HF_Speculation, 'LimitPrice': 0.25, 'VolumeTotalOriginal': 1,
                 'TimeCondition': userapidef.KS_OTP_TC_GFD, 'VolumeCondition': userapidef.KS_OTP_VC_AV,
                 'MinVolume': 0, 'ContingentCondition': userapidef.KS_OTP_CC_Immediately, 'StopPrice': 0,
                 'RequestID': self._request_id}
        self._api.req_order_insert(param, self._request_id)

    def on_rsp_order_insert(self, input_order, rsp_err_id, rsp_err_msg, request_id, is_last):
        print(
            self.__class__.__name__, tdapi.get_current_function_name(), input_order, rsp_err_id, rsp_err_msg, request_id,
            is_last)

    def on_rtn_order(self, order):
        print(self.__class__.__name__, tdapi.get_current_function_name(), order)

    def on_rtn_trade(self, trade):
        print(self.__class__.__name__, tdapi.get_current_function_name(), trade)



def run():
    try:
        path = os.getcwd()
        # initial market data
        global md_api, trd_api
        md_api = mdapi.MarketDataApi.create_api(os.path.join(path, "log"))
        spi2 = MyMdSpi(md_api, instruments=['11000071', '11000076'],
                       exchange='SSE',
                       broker_id="31000853",
                       investor_id="20420418",
                       password="123456")
        md_api.register_spi(spi2)
        md_api.register_front("tcp://116.236.247.173:17996")
        md_api.init()

        trd_api = tdapi.TradeApi.create_api(os.path.join(path, "log"))
        spi = MyTrdSpi(trd_api, instruments=['11000071', '11000076'],
                       exchange='SSE',
                       broker_id="31000853",
                       investor_id="20420418",
                       password="123456")
        trd_api.register_spi(spi)
        trd_api.register_front("tcp://116.236.247.173:17996")
        trd_api.init()

        os.system("pause")
        trd_api.release()
        md_api.release()
    except Exception as err:
        print(err)


run()