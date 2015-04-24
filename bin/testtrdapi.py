__author__ = 'yanghua'

import tdapi
import os
import userapidef


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



def run():
    try:
        api = tdapi.TradeApi.create_api("log")
        spi = MyTrdSpi(api, instruments=['11000071', '11000076'],
                       exchange='SSE',
                       broker_id="31000853",
                       investor_id="20420418",
                       password="123456")
        api.register_spi(spi)
        api.register_front("tcp://116.236.247.173:17996")
        api.init()

        os.system("pause")
        api.release()

    except Exception as err:
        print(err)


run()