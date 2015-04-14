#-*- coding=utf-8 -*-
__author__ = 'hua'

import _otp_md
import os


class MarketSpi:

    def __init__(self):
        self.api = None

    def register_api(self, api):
        self.api = api

    def on_front_connected(self):
        pass

    def on_
