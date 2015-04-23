__author__ = 'hua'

import _otp_trd
import os


class TradeSpi:
    def __init__(self):
        self.api = None

    def register_api(self, api):
        self.api = api

    def on_front_connected(self):
        pass

    def on_front_disconnected(self, reason, message):
        pass

    def on_rsp_user_login(self, rsp_user_login, rsp_err_id, rsp_err_msg, request_id, is_last):
        pass

    def on_rsp_user_logout(self, user_logout, rsp_err_id, rsp_err_msg, request_id, is_last):
        pass

    def on_rsp_error(self, rsp_err_id, rsp_err_msg, request_id, is_last):
        pass

    def on_rsp_order_insert(self, input_order, rsp_err_id, rsp_err_msg, request_id, is_last):
        pass

    def on_rsp_order_action(self, input_order_action, rsp_err_id, rsp_err_msg, request_id, is_last):
        pass

    def on_rsp_qry_order(self, order, rsp_err_id, rsp_err_msg, request_id, is_last):
        pass

    def on_rsp_qry_trade(self, trade, rsp_err_id, rsp_err_msg, request_id, is_last):
        pass

    def on_rsp_qry_investor_position(self, investor_position, rsp_err_id, rsp_err_msg, request_id, is_last):
        pass

    def on_rsp_qry_trading_account(self, trading_account, rsp_err_id, rsp_err_msg, request_id, is_last):
        pass

    def on_rsp_qry_investor(self, investor, rsp_err_id, rsp_err_msg, request_id, is_last):
        pass

    def on_rsp_qry_instrument(self, instrument, rsp_err_id, rsp_err_msg, request_id, is_last):
        pass

    def on_rsp_qry_investor_position_detail(self, investor_position_detail, rsp_err_id, rsp_err_msg, request_id,
                                            is_last):
        pass

    def on_rsp_qry_investor_trade_level(self, investor_trade_level, rsp_err_id, rsp_err_msg, request_id, is_last):
        pass

    def on_rtn_order(self, order):
        pass

    def on_rtn_trade(self, trade):
        pass

    def on_rsp_qry_instrument_margin_rate(self, instrument_margin_rate, rsp_err_id, rsp_err_msg, request_id, is_last):
        pass

    def on_rsp_qry_settlement_info_confirm(self, settlement_info_confirm_field, rsp_err_id, rsp_err_msg, request_id,
                                           is_last):
        pass

    def on_rsp_settlement_info_confirm(self, settlement_info_confirm_field, rsp_err_id, rsp_err_msg, request_id,
                                       is_last):
        pass


class TradeApi:
    @staticmethod
    def create_api(flow_path="", is_using_udp=False):
        if flow_path:
            flow_path = os.path.abspath(flow_path)
        api_ptr = _otp_trd.CreateTrdApi(flow_path, is_using_udp, False)
        return TradeApi(api_ptr)

    def __init__(self, api_ptr):
        self.api_ptr = api_ptr

    def init(self):
        return _otp_trd.Init(self.api_ptr)

    def register_front(self, front_address):
        return _otp_trd.RegisterFront(self.api_ptr, front_address)

    def register_spi(self, spi):
        ret = _otp_trd.RegisterSpi(self.api_ptr, spi)
        spi.register_api(self)
        return ret

    def req_user_login(self, user_login_field, request_id):
        return _otp_trd.ReqUserLogin(self.api_ptr, user_login_field, request_id)

    def req_user_logout(self, user_logout, request_id):
        return _otp_trd.ReqUserLogout(self.api_ptr, user_logout, request_id)

    def join(self):
        return _otp_trd.Join(self.api_ptr)

    def subscribe_private_topic(self, resume_type):
        return _otp_trd.SubscribePrivateTopic(self.api_ptr, resume_type)

    def subscribe_public_topic(self, resume_type):
        return _otp_trd.SubscribePublicTopic(self.api_ptr, resume_type)

    def release(self):
        return _otp_trd.Release(self.api_ptr)

    def get_trading_day(self):
        return _otp_trd.GetTradingDay(self.api_ptr)

    def req_order_insert(self, input_order_field, request_id):
        return _otp_trd.ReqOrderInsert(self.api_ptr, input_order_field, request_id)

    def req_order_action(self, input_order_action_field, request_id):
        return _otp_trd.ReqOrderAction(self.api_ptr, input_order_action_field, request_id)

    def req_qry_order(self, qry_order_field, request_id):
        return _otp_trd.ReqQryOrder(self.api_ptr, qry_order_field, request_id)

    def req_qry_trade(self, qry_trade_field, request_id):
        return _otp_trd.ReqQryTrade(self.api_ptr, qry_trade_field, request_id)

    def req_qry_investor_position(self, qry_investor_position, request_id):
        return _otp_trd.ReqQryInvestorPosition(self.api_ptr, qry_investor_position, request_id)

    def req_qry_trading_account(self, qry_trading_account_field, request_id):
        return _otp_trd.ReqQryTradingAccount(self.api_ptr, qry_trading_account_field, request_id)

    def req_qry_investor(self, qry_investor_field, request_id):
        return _otp_trd.ReqQryInvestor(self.api_ptr, qry_investor_field, request_id)

    def req_qry_instrument(self, qry_instrument_field, request_id):
        return _otp_trd.ReqQryInstrument(self.api_ptr, qry_instrument_field, request_id)

    def req_qry_investor_position_detail(self, qry_investor_position_detail_field, request_id):
        return _otp_trd.ReqQryInvestorPositionDetail(self.api_ptr, qry_investor_position_detail_field, request_id)

    def req_qry_otp_ins_comm_rate(self, qry_otp_ins_comm_rate_field, request_id):
        return _otp_trd.ReqQryOTPInsCommRate(self.api_ptr, qry_otp_ins_comm_rate_field, request_id)

    def req_qry_otp_ins_margin_rate(self, qry_instrument_margin_rate_field, request_id):
        return _otp_trd.ReqQryOTPInsMarginRate(self.api_ptr, qry_instrument_margin_rate_field, request_id)

    def req_qry_investor_trade_level(self, qry_investor_trade_level_field, request_id):
        return _otp_trd.ReqQryInvestorTradeLevel(self.api_ptr, qry_investor_trade_level_field, request_id)

    def req_settlement_info_confirm(self, settlement_info_confirm_field, request_id):
        return _otp_trd.ReqSettlementInfoConfirm(self.api_ptr, settlement_info_confirm_field, request_id)

    def req_qry_settlement_info(self, qry_settlement_info_field, request_id):
        return _otp_trd.ReqQrySettlementInfo(self.api_ptr, qry_settlement_info_field, request_id)
