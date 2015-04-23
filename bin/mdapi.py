# -*- coding=utf-8 -*-
__author__ = 'hua'

import _otp_md
import os


class MarketDataSpi:
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

    def on_rsp_sub_market_data(self, specific_instrument, rsp_err_id, rsp_err_msg, request_id, is_last):
        pass

    def on_rsp_unsub_market_data(self, specific_instrument, rsp_err_id, rsp_err_msg, request_id, is_last):
        pass

    def on_rtn_depth_market_data(self, depth_market_data):
        pass


class MarketDataApi:
    @staticmethod
    def create_api(flow_path="", is_using_udp=False):
        if flow_path:
            flow_path = os.path.abspath(flow_path)
        api_ptr = _otp_md.create_MdApi(flow_path, is_using_udp, False)
        return MarketDataApi(api_ptr)

    def __init__(self, api_ptr):
        self.api_ptr = api_ptr

    def req_user_logout(self, user_logout, request_id):
        return _otp_md.ReqUserLogout(self.api_ptr, user_logout, request_id)

    def join(self):
        return _otp_md.Join(self.api_ptr)

    def unsubscribe_market_data(self, instrument_ids):
        return _otp_md.UnSubscribeMarketData(self.api_ptr, instrument_ids)

    def register_front(self, front_address):
        return _otp_md.RegisterFront(self.api_ptr, front_address)

    def init(self):
        return _otp_md.Init(self.api_ptr)

    def req_user_login(self, req_user_login_field, request_id):
        return _otp_md.ReqUserLogin(self.api_ptr, req_user_login_field, request_id)

    def release(self):
        return _otp_md.Release(self.api_ptr)

    def get_trading_day(self):
        return _otp_md.GetTradingDay(self.api_ptr)

    def subscribe_market_data(self, instrument_ids):
        return _otp_md.SubscribeMarketData(self.api_ptr, instrument_ids)

    def register_spi(self, spi):
        ret = _otp_md.RegisterSpi(self.api_ptr, spi)
        spi.register_api(self)
        return ret