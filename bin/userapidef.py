# -*- coding=utf-8 -*-

__author__ = 'yanghua'


# KSOTP_TE_RESUME_TYPE
KS_OTP_TERT_RESTART = 0
KS_OTP_TERT_RESUME = 1
KS_OTP_TERT_QUICK = 2


# -----------------------------------------------------
# TKSOTPTraderIDType是一个交易所交易员代码类型
# -----------------------------------------------------
# typedef char TKSOTPTraderIDType[21];

# -----------------------------------------------------
# TKSOTPInvestorIDType是一个投资者代码类型
# -----------------------------------------------------
# typedef char TKSOTPInvestorIDType[13];

# -----------------------------------------------------
# TKSOTPBrokerIDType是一个经纪公司代码类型
# -----------------------------------------------------
# typedef char TKSOTPBrokerIDType[11];

# -----------------------------------------------------
# TKSOTPBrokerAbbrType是一个经纪公司简称类型
# -----------------------------------------------------
# typedef char TKSOTPBrokerAbbrType[9];

# -----------------------------------------------------
# TKSOTPBrokerNameType是一个经纪公司名称类型
# -----------------------------------------------------
# typedef char TKSOTPBrokerNameType[81];

# -----------------------------------------------------
# TKSOTPExchangeInstIDType是一个合约在交易所的代码类型
# -----------------------------------------------------
# typedef char TKSOTPExchangeInstIDType[31];

# -----------------------------------------------------
# TKSOTPOrderRefType是一个报单引用类型
# -----------------------------------------------------
# typedef char TKSOTPOrderRefType[13];

# -----------------------------------------------------
# TKSOTPParticipantIDType是一个会员代码类型
# -----------------------------------------------------
# typedef char TKSOTPParticipantIDType[11];

# -----------------------------------------------------
# TKSOTPUserIDType是一个用户代码类型
# -----------------------------------------------------
# typedef char TKSOTPUserIDType[16];

# -----------------------------------------------------
# TKSOTPPasswordType是一个密码类型
# -----------------------------------------------------
# typedef char TKSOTPPasswordType[41];

# -----------------------------------------------------
# TKSOTPClientIDType是一个合约账号类型
# -----------------------------------------------------
# typedef char TKSOTPClientIDType[11];

# -----------------------------------------------------
# TKSOTPInstrumentIDType是一个合约代码类型
# -----------------------------------------------------
# typedef char TKSOTPInstrumentIDType[31];

# -----------------------------------------------------
# TFtdcUnderlyingMultipleType是一个基础商品乘数类型
# -----------------------------------------------------
# typedef double TKSOTPUnderlyingMultipleType;

# -----------------------------------------------------
# TKSOTPMarketIDType是一个市场代码类型
# -----------------------------------------------------
# typedef char TKSOTPMarketIDType[31];

# -----------------------------------------------------
# TKSOTPProductNameType是一个产品名称类型
# -----------------------------------------------------
# typedef char TKSOTPProductNameType[21];

# -----------------------------------------------------
# TKSOTPExchangeIDType是一个交易所代码类型
# -----------------------------------------------------
# typedef char TKSOTPExchangeIDType[9];

# -----------------------------------------------------
# TKSOTPExchangeNameType是一个交易所名称类型
# -----------------------------------------------------
# typedef char TKSOTPExchangeNameType[31];

# -----------------------------------------------------
# TKSOTPExchangeAbbrType是一个交易所简称类型
# -----------------------------------------------------
# typedef char TKSOTPExchangeAbbrType[9];

# -----------------------------------------------------
# TKSOTPExchangeFlagType是一个交易所标志类型
# -----------------------------------------------------
# typedef char TKSOTPExchangeFlagType[2];

# -----------------------------------------------------
# TKSOTPMacAddressType是一个Mac地址类型
# -----------------------------------------------------
# typedef char TKSOTPMacAddressType[21];

# -----------------------------------------------------
# TKSOTPDateType是一个日期类型
# -----------------------------------------------------
# typedef char TKSOTPDateType[9];

# -----------------------------------------------------
# TKSOTPTimeType是一个时间类型
# -----------------------------------------------------
# typedef char TKSOTPTimeType[9];

# -----------------------------------------------------
# TKSOTPLongTimeType是一个长时间类型
# -----------------------------------------------------
# typedef char TKSOTPLongTimeType[13];

# -----------------------------------------------------
# TKSOTPInstrumentNameType是一个合约名称类型
# -----------------------------------------------------
# typedef char TKSOTPInstrumentNameType[21];

# -----------------------------------------------------
# TKSOTPOrderSysIDType是一个报单编号类型
# -----------------------------------------------------
# typedef char TKSOTPOrderSysIDType[21];

# -----------------------------------------------------
# TKSOTPTradeIDType是一个成交编号类型
# -----------------------------------------------------
# typedef char TKSOTPTradeIDType[21];

# -----------------------------------------------------
# TKSOTPCommandTypeType是一个DB命令类型类型
# -----------------------------------------------------
# typedef char TKSOTPCommandTypeType[65];

# -----------------------------------------------------
# TKSOTPIPAddressType是一个IP地址类型
# -----------------------------------------------------
# typedef char TKSOTPIPAddressType[16];

# -----------------------------------------------------
# TKSOTPProductInfoType是一个产品信息类型
# -----------------------------------------------------
# typedef char TKSOTPProductInfoType[11];

# -----------------------------------------------------
# TKSOTPProtocolInfoType是一个协议信息类型
# -----------------------------------------------------
# typedef char TKSOTPProtocolInfoType[11];

# -----------------------------------------------------
# TKSOTPBusinessUnitType是一个业务单元类型
# -----------------------------------------------------
# typedef char TKSOTPBusinessUnitType[21];

# -----------------------------------------------------
# TKSOTPDepositSeqNoType是一个出入金流水号类型
# -----------------------------------------------------
# typedef char TKSOTPDepositSeqNoType[15];

# -----------------------------------------------------
# TKSOTPIdentifiedCardNoType是一个证件号码类型
# -----------------------------------------------------
# typedef char TKSOTPIdentifiedCardNoType[51];

# -----------------------------------------------------
# TKSOTPIdCardTypeType是一个证件类型类型
# -----------------------------------------------------
# 组织机构代码
KS_OTP_ICT_EID = '0'
# 身份证
KS_OTP_ICT_IDCard = '1'
# 军官证
KS_OTP_ICT_OfficerIDCard = '2'
# 警官证
KS_OTP_ICT_PoliceIDCard = '3'
# 士兵证
KS_OTP_ICT_SoldierIDCard = '4'
# 户口簿
KS_OTP_ICT_HouseholdRegister = '5'
# 护照
KS_OTP_ICT_Passport = '6'
# 台胞证
KS_OTP_ICT_TaiwanCompatriotIDCard = '7'
# 回乡证
KS_OTP_ICT_HomeComingCard = '8'
# 营业执照号
KS_OTP_ICT_LicenseNo = '9'
# 税务登记号
KS_OTP_ICT_TaxNo = 'A'
# 其他证件
KS_OTP_ICT_OtherCard = 'x'

# typedef char TKSOTPIdCardTypeType;

# -----------------------------------------------------
# TKSOTPOrderLocalIDType是一个本地报单编号类型
# -----------------------------------------------------
# typedef char TKSOTPOrderLocalIDType[13];

# -----------------------------------------------------
# TKSOTPPartyNameType是一个参与人名称类型
# -----------------------------------------------------
# typedef char TKSOTPPartyNameType[81];

# -----------------------------------------------------
# TKSOTPErrorMsgType是一个错误信息类型
# -----------------------------------------------------
# typedef char TKSOTPErrorMsgType[81];

# -----------------------------------------------------
# TKSOTPFieldNameType是一个字段名类型
# -----------------------------------------------------
# typedef char TKSOTPFieldNameType[2049];

# -----------------------------------------------------
# TKSOTPFieldContentType是一个字段内容类型
# -----------------------------------------------------
# typedef char TKSOTPFieldContentType[2049];

# -----------------------------------------------------
# TKSOTPSystemNameType是一个系统名称类型
# -----------------------------------------------------
# typedef char TKSOTPSystemNameType[41];

# -----------------------------------------------------
# TKSOTPContentType是一个消息正文类型
# -----------------------------------------------------
# typedef char TKSOTPContentType[501];

# -----------------------------------------------------
# TKSOTPOrderActionStatusType是一个报单操作状态类型
# -----------------------------------------------------
# 已经提交
KS_OTP_OAS_Submitted = 'a'
# 已经接受
KS_OTP_OAS_Accepted = 'b'
# 已经被拒绝
KS_OTP_OAS_Rejected = 'c'

# typedef char TKSOTPOrderActionStatusType;

# -----------------------------------------------------
# TKSOTPOrderStatusType是一个报单状态类型
# -----------------------------------------------------
# 全部成交
KS_OTP_OST_AllTraded = '0'
# 部分成交还在队列中
KS_OTP_OST_PartTradedQueueing = '1'
# 部分成交不在队列中
KS_OTP_OST_PartTradedNotQueueing = '2'
# 未成交还在队列中
KS_OTP_OST_NoTradeQueueing = '3'
# 未成交不在队列中
KS_OTP_OST_NoTradeNotQueueing = '4'
# 撤单
KS_OTP_OST_Canceled = '5'
# 未知
KS_OTP_OST_Unknown = 'a'
# 尚未触发
KS_OTP_OST_NotTouched = 'b'
# 已触发
KS_OTP_OST_Touched = 'c'

# typedef char TKSOTPOrderStatusType;

# -----------------------------------------------------
# TKSOTPOrderSubmitStatusType是一个报单提交状态类型
# -----------------------------------------------------
# 已经提交
KS_OTP_OSS_InsertSubmitted = '0'
# 撤单已经提交
KS_OTP_OSS_CancelSubmitted = '1'
# 修改已经提交
KS_OTP_OSS_ModifySubmitted = '2'
# 已经接受
KS_OTP_OSS_Accepted = '3'
# 报单已经被拒绝
KS_OTP_OSS_InsertRejected = '4'
# 撤单已经被拒绝
KS_OTP_OSS_CancelRejected = '5'
# 改单已经被拒绝
KS_OTP_OSS_ModifyRejected = '6'

# typedef char TKSOTPOrderSubmitStatusType;

# -----------------------------------------------------
# TKSOTPPositionDateType是一个持仓日期类型
# -----------------------------------------------------
# 今日持仓
KS_OTP_PSD_Today = '1'
# 历史持仓
KS_OTP_PSD_History = '2'

# typedef char TKSOTPPositionDateType;

# -----------------------------------------------------
# TKSOTPPositionDateTypeType是一个持仓日期类型类型
# -----------------------------------------------------
# 使用历史持仓
KS_OTP_PDT_UseHistory = '1'
# 不使用历史持仓
KS_OTP_PDT_NoUseHistory = '2'

# typedef char TKSOTPPositionDateTypeType;

# -----------------------------------------------------
# TKSOTPTradingRoleType是一个交易角色类型
# -----------------------------------------------------
# 代理
KS_OTP_ER_Broker = '1'
# 自营
KS_OTP_ER_Host = '2'
# 做市商
KS_OTP_ER_Maker = '3'

# typedef char TKSOTPTradingRoleType;

# -----------------------------------------------------
# TKSOTPProductClassType是一个产品类型类型
# -----------------------------------------------------
# 期货
KS_OTP_PC_Futures = '1'
# 期货期权
KS_OTP_PC_Options = '2'
# 组合
KS_OTP_PC_Combination = '3'
# 即期
KS_OTP_PC_Spot = '4'
# 期转现
KS_OTP_PC_EFP = '5'
# 现货期权
KS_OTP_PC_SpotOption = '6'
# 个股期权
KS_OTP_PC_ETFOption = '7'
# 证券
KS_OTP_PC_Stock = '8'

# typedef char TKSOTPProductClassType;

# -----------------------------------------------------
# TKSOTPInstLifePhaseType是一个合约生命周期状态类型
# -----------------------------------------------------
# 未上市
KS_OTP_IP_NotStart = '0'
# 上市
KS_OTP_IP_Started = '1'
# 停牌
KS_OTP_IP_Pause = '2'
# 到期
KS_OTP_IP_Expired = '3'

# typedef char TKSOTPInstLifePhaseType;

# -----------------------------------------------------
# TKSOTPDirectionType是一个买卖方向类型
# -----------------------------------------------------
# 买
KS_OTP_D_Buy = '0'
# 卖
KS_OTP_D_Sell = '1'

# typedef char TKSOTPDirectionType;

# -----------------------------------------------------
# TKSOTPPositionTypeType是一个持仓类型类型
# -----------------------------------------------------
# 净持仓
KS_OTP_PT_Net = '1'
# 综合持仓
KS_OTP_PT_Gross = '2'

# typedef char TKSOTPPositionTypeType;

# -----------------------------------------------------
# TKSOTPHedgeFlagType是一个备兑标志类型
# -----------------------------------------------------
# 投机
KS_OTP_HF_Speculation = '1'
# 套利
KS_OTP_HF_Arbitrage = '2'
# 套保
KS_OTP_HF_Hedge = '3'
# 备兑
KS_OTP_HF_Covered = '4'

# typedef char TKSOTPHedgeFlagType;

# -----------------------------------------------------
# TKSOTPClientIDTypeType是一个交易编码类型类型
# -----------------------------------------------------
# 投机# 非备兑
KS_OTP_CIDT_UnCovered = '1'
# 套利
THOST_FTDC_CIDT_Arbitrage = '2'
# 套保# 备兑
KS_OTP_CIDT_Covered = '3'

# typedef char TKSOTPClientIDTypeType;

# -----------------------------------------------------
# TKSOTPOrderPriceTypeType是一个报单价格条件类型
# -----------------------------------------------------
# 任意价
KS_OTP_OPT_AnyPrice = '1'
# 限价
KS_OTP_OPT_LimitPrice = '2'
# 最优价
KS_OTP_OPT_BestPrice = '3'
# 最新价
KS_OTP_OPT_LastPrice = '4'

# typedef char TKSOTPOrderPriceTypeType;

# -----------------------------------------------------
# TKSOTPOffsetFlagType是一个开平标志类型
# -----------------------------------------------------
# 开仓
KS_OTP_OF_Open = '0'
# 平仓
KS_OTP_OF_Close = '1'
# 强平
KS_OTP_OF_ForceClose = '2'
# 平今
KS_OTP_OF_CloseToday = '3'
# 平昨
KS_OTP_OF_CloseYesterday = '4'
# 强减
KS_OTP_OF_ForceOff = '5'
# 本地强平
KS_OTP_OF_LocalForceClose = '6'

# typedef char TKSOTPOffsetFlagType;

# -----------------------------------------------------
# TKSOTPForceCloseReasonType是一个强平原因类型
# -----------------------------------------------------
# 非强平
KS_OTP_FCC_NotForceClose = '0'
# 资金不足
KS_OTP_FCC_LackDeposit = '1'
# 客户超仓
KS_OTP_FCC_ClientOverPositionLimit = '2'
# 会员超仓
KS_OTP_FCC_MemberOverPositionLimit = '3'
# 持仓非整数倍
KS_OTP_FCC_NotMultiple = '4'
# 违规
KS_OTP_FCC_Violation = '5'
# 其它
KS_OTP_FCC_Other = '6'
# 自然人临近交割
KS_OTP_FCC_PersonDeliv = '7'

# typedef char TKSOTPForceCloseReasonType;

# -----------------------------------------------------
# TKSOTPOrderTypeType是一个报单类型类型
# -----------------------------------------------------
# 正常
KS_OTP_ORDT_Normal = '0'
# 报价衍生
KS_OTP_ORDT_DeriveFromQuote = '1'

# typedef char TKSOTPOrderTypeType;

# -----------------------------------------------------
# TKSOTPTimeConditionType是一个有效期类型类型
# -----------------------------------------------------
# 立即完成，否则撤销
KS_OTP_TC_IOC = '1'
# 本节有效
KS_OTP_TC_GFS = '2'
# 当日有效
KS_OTP_TC_GFD = '3'
# 指定日期前有效
KS_OTP_TC_GTD = '4'
# 撤销前有效
KS_OTP_TC_GTC = '5'
# 集合竞价有效
KS_OTP_TC_GFA = '6'

# typedef char TKSOTPTimeConditionType;

# -----------------------------------------------------
# TKSOTPVolumeConditionType是一个成交量类型类型
# -----------------------------------------------------
# 任何数量
KS_OTP_VC_AV = '1'
# 最小数量
KS_OTP_VC_MV = '2'
# 全部数量
KS_OTP_VC_CV = '3'

# typedef char TKSOTPVolumeConditionType;

# -----------------------------------------------------
# TKSOTPContingentConditionType是一个触发条件类型
# -----------------------------------------------------
# 立即
KS_OTP_CC_Immediately = '1'
# 止损
KS_OTP_CC_Touch = '2'
# 止赢
KS_OTP_CC_TouchProfit = '3'

# typedef char TKSOTPContingentConditionType;

# -----------------------------------------------------
# TKSOTPActionFlagType是一个操作标志类型
# -----------------------------------------------------
# 删除
KS_OTP_AF_Delete = '0'
# 修改
KS_OTP_AF_Modify = '3'

# typedef char TKSOTPActionFlagType;

# -----------------------------------------------------
# TKSOTPOrderSourceType是一个报单来源类型
# -----------------------------------------------------
# 来自参与者
KS_OTP_OSRC_Participant = '0'
# 来自管理员
KS_OTP_OSRC_Administrator = '1'

# typedef char TKSOTPOrderSourceType;

# -----------------------------------------------------
# TKSOTPTradeTypeType是一个成交类型类型
# -----------------------------------------------------
# 普通成交
KS_OTP_TRDT_Common = '0'
# 期权执行
KS_OTP_TRDT_OptionsOTPution = '1'
# OTC成交
KS_OTP_TRDT_OTC = '2'
# 期转现衍生成交
KS_OTP_TRDT_EFPDerived = '3'

# typedef char TKSOTPTradeTypeType;

# -----------------------------------------------------
# TKSOTPPriceSourceType是一个成交价来源类型
# -----------------------------------------------------
# 前成交价
KS_OTP_PSRC_LastPrice = '0'
# 买委托价
KS_OTP_PSRC_Buy = '1'
# 卖委托价
KS_OTP_PSRC_Sell = '2'

# typedef char TKSOTPPriceSourceType;

# -----------------------------------------------------
# TKSOTPInstrumentStatusType是一个合约交易状态类型
# -----------------------------------------------------
# 开盘前
KS_OTP_IS_BeforeTrading = '0'
# 非交易
KS_OTP_IS_NoTrading = '1'
# 连续交易
KS_OTP_IS_Continous = '2'
# 集合竞价报单
KS_OTP_IS_AuctionOrdering = '3'
# 集合竞价价格平衡
KS_OTP_IS_AuctionBalance = '4'
# 集合竞价撮合
KS_OTP_IS_AuctionMatch = '5'
# 收盘
KS_OTP_IS_Closed = '6'

# typedef char TKSOTPInstrumentStatusType;

# -----------------------------------------------------
# TKSOTPInstStatusEnterReasonType是一个品种进入交易状态原因类型
# -----------------------------------------------------
# 自动切换
KS_OTP_IER_Automatic = '1'
# 手动切换
KS_OTP_IER_Manual = '2'
# 熔断
KS_OTP_IER_Fuse = '3'

# typedef char TKSOTPInstStatusEnterReasonType;

# -----------------------------------------------------
# TKSOTPOrderActionRefType是一个报单操作引用类型
# -----------------------------------------------------
# typedef int TKSOTPOrderActionRefType;

# -----------------------------------------------------
# TKSOTPInstallCountType是一个安装数量类型
# -----------------------------------------------------
# typedef int TKSOTPInstallCountType;

# -----------------------------------------------------
# TKSOTPInstallIDType是一个安装编号类型
# -----------------------------------------------------
# typedef int TKSOTPInstallIDType;

# -----------------------------------------------------
# TKSOTPErrorIDType是一个错误代码类型
# -----------------------------------------------------
# typedef int TKSOTPErrorIDType;

# -----------------------------------------------------
# TKSOTPSettlementIDType是一个结算编号类型
# -----------------------------------------------------
# typedef int TKSOTPSettlementIDType;

# -----------------------------------------------------
# TKSOTPVolumeType是一个数量类型
# -----------------------------------------------------
# typedef int TKSOTPVolumeType;

# -----------------------------------------------------
# TKSOTPFrontIDType是一个前置编号类型
# -----------------------------------------------------
# typedef int TKSOTPFrontIDType;

# -----------------------------------------------------
# TKSOTPSessionIDType是一个会话编号类型
# -----------------------------------------------------
# typedef int TKSOTPSessionIDType;

# -----------------------------------------------------
# TKSOTPSequenceNoType是一个序号类型
# -----------------------------------------------------
# typedef int TKSOTPSequenceNoType;

# -----------------------------------------------------
# TKSOTPMillisecType是一个时间（毫秒）类型
# -----------------------------------------------------
# typedef int TKSOTPMillisecType;

# -----------------------------------------------------
# TKSOTPVolumeMultipleType是一个合约数量乘数类型
# -----------------------------------------------------
# typedef int TKSOTPVolumeMultipleType;

# -----------------------------------------------------
# TKSOTPTradingSegmentSNType是一个交易阶段编号类型
# -----------------------------------------------------
# typedef int TKSOTPTradingSegmentSNType;

# -----------------------------------------------------
# TKSOTPRequestIDType是一个请求编号类型
# -----------------------------------------------------
# typedef int TKSOTPRequestIDType;

# -----------------------------------------------------
# TKSOTPYearType是一个年份类型
# -----------------------------------------------------
# typedef int TKSOTPYearType;

# -----------------------------------------------------
# TKSOTPMonthType是一个月份类型
# -----------------------------------------------------
# typedef int TKSOTPMonthType;

# -----------------------------------------------------
# TKSOTPBoolType是一个布尔型类型
# -----------------------------------------------------
# typedef int TKSOTPBoolType;

# -----------------------------------------------------
# TKSOTPPriceType是一个价格类型
# -----------------------------------------------------
# typedef double TKSOTPPriceType;

# -----------------------------------------------------
# TKSOTPRatioType是一个比率类型
# -----------------------------------------------------
# typedef double TKSOTPRatioType;

# -----------------------------------------------------
# TKSOTPMoneyType是一个资金类型
# -----------------------------------------------------
# typedef double TKSOTPMoneyType;

# -----------------------------------------------------
# TKSOTPLargeVolumeType是一个大额数量类型
# -----------------------------------------------------
# typedef double TKSOTPLargeVolumeType;

# -----------------------------------------------------
# TKSOTPSequenceSeriesType是一个序列系列号类型
# -----------------------------------------------------
# typedef short TKSOTPSequenceSeriesType;

# -----------------------------------------------------
# TKSOTPCommPhaseNoType是一个通讯时段编号类型
# -----------------------------------------------------
# typedef short TKSOTPCommPhaseNoType;

# -----------------------------------------------------
# TKSOTPSequenceLabelType是一个序列编号类型
# -----------------------------------------------------
# typedef char TKSOTPSequenceLabelType[2];

# -----------------------------------------------------
# TKSOTPAddressType是一个通讯地址类型
# -----------------------------------------------------
# typedef char TKSOTPAddressType[101];

# -----------------------------------------------------
# TKSOTPZipCodeType是一个邮政编码类型
# -----------------------------------------------------
# typedef char TKSOTPZipCodeType[7];

# -----------------------------------------------------
# TKSOTPTelephoneType是一个联系电话类型
# -----------------------------------------------------
# typedef char TKSOTPTelephoneType[41];

# -----------------------------------------------------
# TKSOTPFaxType是一个传真类型
# -----------------------------------------------------
# typedef char TKSOTPFaxType[41];

# -----------------------------------------------------
# TKSOTPMobileType是一个手机类型
# -----------------------------------------------------
# typedef char TKSOTPMobileType[41];

# -----------------------------------------------------
# TKSOTPEMailType是一个电子邮件类型
# -----------------------------------------------------
# typedef char TKSOTPEMailType[41];

# -----------------------------------------------------
# TKSOTPMemoType是一个备注类型
# -----------------------------------------------------
# typedef char TKSOTPMemoType[161];

# -----------------------------------------------------
# TKSOTPPropertyIDType是一个属性代码类型
# -----------------------------------------------------
# typedef char TKSOTPPropertyIDType[33];

# -----------------------------------------------------
# TKSOTPPropertyNameType是一个属性名称类型
# -----------------------------------------------------
# typedef char TKSOTPPropertyNameType[65];

# -----------------------------------------------------
# TKSOTPLicenseNoType是一个营业执照号类型
# -----------------------------------------------------
# typedef char TKSOTPLicenseNoType[51];

# -----------------------------------------------------
# TKSOTPSettlementParamValueType是一个参数代码值类型
# -----------------------------------------------------
# typedef char TKSOTPSettlementParamValueType[256];

# -----------------------------------------------------
# TKSOTPBrandCodeType是一个牌号类型
# -----------------------------------------------------
# typedef char TKSOTPBrandCodeType[257];

# -----------------------------------------------------
# TKSOTPWarehouseType是一个仓库类型
# -----------------------------------------------------
# typedef char TKSOTPWarehouseType[257];

# -----------------------------------------------------
# TKSOTPProductDateType是一个产期类型
# -----------------------------------------------------
# typedef char TKSOTPProductDateType[41];

# -----------------------------------------------------
# TKSOTPGradeType是一个等级类型
# -----------------------------------------------------
# typedef char TKSOTPGradeType[41];

# -----------------------------------------------------
# TKSOTPClassifyType是一个类别类型
# -----------------------------------------------------
# typedef char TKSOTPClassifyType[41];

# -----------------------------------------------------
# TKSOTPAccountIDType是一个投资者帐号类型
# -----------------------------------------------------
# typedef char TKSOTPAccountIDType[13];


# -----------------------------------------------------
# TKSOTPProductLifePhaseType是一个产品生命周期状态类型
# -----------------------------------------------------
# 活跃
KS_OTP_PLP_Active = '1'
# 不活跃
KS_OTP_PLP_NonActive = '2'
# 注销
KS_OTP_PLP_Canceled = '3'

# typedef char TKSOTPProductLifePhaseType;


# -----------------------------------------------------
# TKSOTPInvestorTypeType是一个投资者类型类型
# -----------------------------------------------------
# 自然人
KS_OTP_CT_Person = '0'
# 法人
KS_OTP_CT_Company = '1'
# 投资基金
KS_OTP_CT_Fund = '2'

# typedef char TKSOTPInvestorTypeType;

# -----------------------------------------------------
# TKSOTPBrokerTypeType是一个经纪公司类型类型
# -----------------------------------------------------
# 交易会员
KS_OTP_BT_Trade = '0'
# 交易结算会员
KS_OTP_BT_TradeSettle = '1'

# typedef char TKSOTPBrokerTypeType;

# -----------------------------------------------------
# TKSOTPCurrencyCodeType是一个币种类型
# -----------------------------------------------------
# typedef char TKSOTPCurrencyCodeType[4];

# -----------------------------------------------------
# TKSOTPCertCodeType是一个证件号码类型
# -----------------------------------------------------
# typedef char TKSOTPCertCodeType[21];

# -----------------------------------------------------
# TKSOTPUserTypeType是一个用户类型类型
# -----------------------------------------------------
# 投资者
KS_OTP_UT_Investor = '0'
# 操作员
KS_OTP_UT_Operator = '1'
# 管理员
KS_OTP_UT_SuperUser = '2'

# typedef char TKSOTPUserTypeType;


# -----------------------------------------------------
# TKSOTPExClientIDTypeType是一个合约账号类型类型
# -----------------------------------------------------
# 非备兑
KS_OTP_ECIDT_UnCovered = '0'
# 备兑
KS_OTP_ECIDT_Covered = '1'

# typedef char TKSOTPExClientIDTypeType;

# -----------------------------------------------------
# TKSOTPUserProductIDType是一个产品标识类型
# -----------------------------------------------------
# typedef char TKSOTPUserProductIDType[33];

# -----------------------------------------------------
# TKSOTPTradeSourceType是一个成交来源类型
# -----------------------------------------------------
# 来自交易所普通回报
KS_OTP_TSRC_NORMAL = '0'
# 来自查询
KS_OTP_TSRC_QUERY = '1'

# typedef char TKSOTPTradeSourceType;

# -----------------------------------------------------
# TKSOTPSRiskRateType是一个风险度类型
# -----------------------------------------------------
# typedef char TKSOTPSRiskRateType[21];

# -----------------------------------------------------
# TKSOTPOptionsTypeType是一个期权类型类型
# -----------------------------------------------------
# 认购
KS_OTP_CP_CallOptions = '1'
# 认沽
KS_OTP_CP_PutOptions = '2'

# typedef char TKSOTPOptionsTypeType;

# -----------------------------------------------------
# TKSOTPActionTypeType是一个执行类型类型
# -----------------------------------------------------
# 执行
KS_OTP_ACTP_Exec = '1'
# 放弃
KS_OTP_ACTP_Abandon = '2'

# typedef char TKSOTPActionTypeType;

# -----------------------------------------------------
# TKSOTPFutureBranchIDType是一个证券分支机构编码类型
# -----------------------------------------------------
# typedef char TKSOTPFutureBranchIDType[31];

# -----------------------------------------------------
# TKSOTPCustTypeType是一个客户类型类型
# -----------------------------------------------------
# 自然人
KS_OTP_CUSTT_Person = '0'
# 机构户
KS_OTP_CUSTT_Institution = '1'

# typedef char TKSOTPCustTypeType;

# -----------------------------------------------------
# TKSOTPIndividualNameType是一个个人姓名类型
# -----------------------------------------------------
# typedef char TKSOTPIndividualNameType[51];

# -----------------------------------------------------
# TKSOTPTradeAmountType是一个交易金额（元）类型
# -----------------------------------------------------
# typedef double TKSOTPTradeAmountType;

# -----------------------------------------------------
# TKSOTPFeePayFlagType是一个费用支付标志类型
# -----------------------------------------------------
# 由受益方支付费用
KS_OTP_FPF_BEN = '0'
# 由发送方支付费用
KS_OTP_FPF_OUR = '1'
# 由发送方支付发起的费用，受益方支付接受的费用
KS_OTP_FPF_SHA = '2'

# typedef char TKSOTPFeePayFlagType;

# -----------------------------------------------------
# TKSOTPCustFeeType是一个应收客户费用（元）类型
# -----------------------------------------------------
# typedef double TKSOTPCustFeeType;

# -----------------------------------------------------
# TKSOTPFutureFeeType是一个应收证券公司费用（元）类型
# -----------------------------------------------------
# typedef double TKSOTPFutureFeeType;

# -----------------------------------------------------
# TKSOTPBankIDType是一个银行代码类型
# -----------------------------------------------------
# typedef char TKSOTPBankIDType[4];

# -----------------------------------------------------
# TKSOTPCurrencyIDType是一个币种代码类型
# -----------------------------------------------------
# typedef char TKSOTPCurrencyIDType[4];

# -----------------------------------------------------
# TKSOTPBankSerialType是一个银行流水号类型
# -----------------------------------------------------
# typedef char TKSOTPBankSerialType[13];

# -----------------------------------------------------
# TKSOTPSerialType是一个流水号类型
# -----------------------------------------------------
# typedef int TKSOTPSerialType;

# -----------------------------------------------------
# TKSOTPLastFragmentType是一个最后分片标志类型
# -----------------------------------------------------
# 是最后分片
KS_OTP_LF_Yes = '0'
# 不是最后分片
KS_OTP_LF_No = '1'

# typedef char TKSOTPLastFragmentType;

# -----------------------------------------------------
# TKSOTPFutureSerialType是一个证券公司流水号类型
# -----------------------------------------------------
# typedef int TKSOTPFutureSerialType;

# -----------------------------------------------------
# TKSOTPBankAccountType是一个银行账户类型
# -----------------------------------------------------
# typedef char TKSOTPBankAccountType[41];

# -----------------------------------------------------
# TKSOTPTradeDateType是一个交易日期类型
# -----------------------------------------------------
# typedef char TKSOTPTradeDateType[9];

# -----------------------------------------------------
# TKSOTPTradeTimeType是一个交易时间类型
# -----------------------------------------------------
# typedef char TKSOTPTradeTimeType[9];

# -----------------------------------------------------
# TKSOTPTradeCodeType是一个交易代码类型
# -----------------------------------------------------
# typedef char TKSOTPTradeCodeType[7];

# -----------------------------------------------------
# TKSOTPDigestType是一个摘要类型
# -----------------------------------------------------
# typedef char TKSOTPDigestType[36];

# -----------------------------------------------------
# TKSOTPTransferStatusType是一个转账交易状态类型
# -----------------------------------------------------
# 正常
TKS_OTP_TRFS_Normal = '0'
# 被冲正
TKS_OTP_TRFS_Repealed = '1'

# typedef char TKSOTPTransferStatusType;

# -----------------------------------------------------
# TKSOTPBankAccTypeType是一个银行帐号类型类型
# -----------------------------------------------------
# 银行存折
TKS_OTP_BAT_BankBook = '1'
# 储蓄卡
TKS_OTP_BAT_SavingCard = '2'
# 信用卡
TKS_OTP_BAT_CreditCard = '3'

# typedef char TKSOTPBankAccTypeType;

# -----------------------------------------------------
# TKSOTPDeviceIDType是一个渠道标志类型
# -----------------------------------------------------
# typedef char TKSOTPDeviceIDType[3];

# -----------------------------------------------------
# TKSOTPBankCodingForFutureType是一个银行对证券公司的编码类型
# -----------------------------------------------------
# typedef char TKSOTPBankCodingForFutureType[33];

# -----------------------------------------------------
# TKSOTPBankBrchIDType是一个银行分中心代码类型
# -----------------------------------------------------
# typedef char TKSOTPBankBrchIDType[5];

# -----------------------------------------------------
# TKSOTPNoIndicatorType是一个是或否标识类型
# -----------------------------------------------------
# 是
KS_OTP_YNI_Yes = '0'
# 否
KS_OTP_YNI_No = '1'

# typedef char TKSOTPYesNoIndicatorType;

# -----------------------------------------------------
# TKSOTPAddInfoType是一个附加信息类型
# -----------------------------------------------------
# typedef char TKSOTPAddInfoType[129];

# -----------------------------------------------------
# TKSOTPPwdFlagType是一个密码核对标志类型
# -----------------------------------------------------
# 不核对
KS_OTP_BPWDF_NoCheck = '0'
# 明文核对
KS_OTP_BPWDF_BlankCheck = '1'
# 密文核对
KS_OTP_BPWDF_EncryptCheck = '2'

# typedef char TKSOTPPwdFlagType;

# -----------------------------------------------------
# TKSOTPBankOperNoType是一个银行操作员号类型
# -----------------------------------------------------
# typedef char TKSOTPBankOperNoType[4];

# -----------------------------------------------------
# TKSOTPTargetIDType是一个同步目标编号类型
# -----------------------------------------------------
# typedef char TKSOTPTargetIDType[4];

# -----------------------------------------------------
# TKSOTPOperNoType是一个交易柜员类型
# -----------------------------------------------------
# typedef char TKSOTPOperNoType[17];

# -----------------------------------------------------
# TKSOTPTIDType是一个交易ID类型
# -----------------------------------------------------
# typedef int TKSOTPTIDType;

# -----------------------------------------------------
# TKSOTPOperNoType是一个交易柜员类型
# -----------------------------------------------------
# typedef char TKSOTPOperNoType[17];

# -----------------------------------------------------
# TKSOTPBankNameType是一个银行名称类型
# -----------------------------------------------------
# typedef char TKSOTPBankNameType[101];

# -----------------------------------------------------
# TKSOTPTradeCodeType是一个交易代码类型
# -----------------------------------------------------
# typedef char TKSOTPTradeCodeType[7];

# -----------------------------------------------------
# TKSOTPBankIDType是一个银行代码类型
# -----------------------------------------------------
# typedef char TKSOTPBankIDType[4];

# -----------------------------------------------------
# TKSOTPBankBrchIDType是一个银行分中心代码类型
# -----------------------------------------------------
# typedef char TKSOTPBankBrchIDType[5];

# -----------------------------------------------------
# TKSOTPPlateSerialType是一个平台流水号类型
# -----------------------------------------------------
# typedef int TKSOTPPlateSerialType;

# -----------------------------------------------------
# TKSOTPFutureAccTypeType是一个证券公司帐号类型类型
# -----------------------------------------------------
# 银行存折
KS_OTP_FAT_BankBook = '1'
# 储蓄卡
KS_OTP_FAT_SavingCard = '2'
# 信用卡
KS_OTP_FAT_CreditCard = '3'

# typedef char TKSOTPFutureAccTypeType;

# -----------------------------------------------------
# TKSOTPAvailabilityFlagType是一个有效标志类型
# -----------------------------------------------------
# 未确认
KS_OTP_AVAF_Invalid = '0'
# 有效
KS_OTP_AVAF_Valid = '1'
# 冲正
KS_OTP_AVAF_Repeal = '2'

# typedef char TKSOTPAvailabilityFlagType;

# -----------------------------------------------------
# TKSOTPOperatorCodeType是一个操作员类型
# -----------------------------------------------------
# typedef char TKSOTPOperatorCodeType[17];

# -----------------------------------------------------
# TKSOTPProtectFlagType是一个保护性标志类型
# -----------------------------------------------------
# # 保护
KSOTP_PF_True = 'T'
# # 非保护
KSOTP_PF_Flase = 'F'

# typedef char TKSOTPProtectFlagType;

# -----------------------------------------------------
# TKSOTPControlRangeType是一个控制范围类型
# -----------------------------------------------------
# # 品种
KSOTP_CR_Product = '0'
# # 所有
KSOTP_CR_ALL = '1'

# typedef char TKSOTPControlRangeType;

# -----------------------------------------------------
# TKSOTPTradeLevelType是一个交易级别类型
# -----------------------------------------------------
# # 一级
KSOTP_TL_Level1 = '1'
# # 二级
KSOTP_TL_Level2 = '2'
# # 三级
KSOTP_TL_Level3 = '3'

# typedef char TKSOTPTradeLevelType;

# -----------------------------------------------------
# TKSOTPPosiDirectionType是一个个股持仓方向类型
# -----------------------------------------------------
# # 权利仓
KSVOC_PD_Buy = '2'
# # 义务仓
KSVOC_PD_Sell = '3'

# typedef char TKSOTPPosiDirectionType;

# -----------------------------------------------------
# TKSOTPDelivModeType是一个个股交收查询类型
# -----------------------------------------------------
# # 行权标的净额交收
KSVOC_DM_Product = '1'
# # 行权现金结算交收明细
KSVOC_DM_Cash = '2'
# # 行权违约处置扣券及返还
KSVOC_DM_Dispos = '3'

# typedef char TKSOTPDelivModeType;

# -----------------------------------------------------
# TKSOTPFunctionNameType是一个功能名称类型
# -----------------------------------------------------
# typedef char TKSOTPFunctionNameType[65];

# -----------------------------------------------------
# TKSOTPStrikeTypeType是一个执行类型类型
# -----------------------------------------------------
# 自身对冲
KS_OTP_STT_Hedge = '0'
# 匹配执行
KS_OTP_STT_Match = '1'

# typedef char TKSOTPStrikeTypeType;

# -----------------------------------------------------
# TKSOTPExecOrderPositionFlagType是一个期权行权后是否保留头寸的标记类型
# -----------------------------------------------------
# 保留
KS_OTP_EOPF_Reserve = '0'
# 不保留
KS_OTP_EOPF_UnReserve = '1'

# typedef char TKSOTPExecOrderPositionFlagType;

# -----------------------------------------------------
# TKSOTPExecOrderCloseFlagType是一个期权行权后生成的头寸是否自动平仓类型
# -----------------------------------------------------
# 自动平仓
KS_OTP_EOCF_AutoClose = '0'
# 免于自动平仓
KS_OTP_EOCF_NotToClose = '1'  # typedef char TKSOTPExecOrderCloseFlagType;

# -----------------------------------------------------
# TKSOTPLockTypeType是一个锁定方向类型
# -----------------------------------------------------
# 锁定
KS_OTP_LCKT_Lock = '1'
# 解锁
KS_OTP_LCKT_Unlock = '2'

# typedef char TKSOTPLockTypeType;

# -----------------------------------------------------
# TKSOTPExecOrderSysIDType是一个执行宣告系统编号类型
# -----------------------------------------------------
# typedef char TKSOTPExecOrderSysIDType[21];

# -----------------------------------------------------
# TKSOTPExecResultType是一个执行结果类型
# -----------------------------------------------------
# 没有执行
KS_OTP_OER_NoExec = 'n'
# 已经取消
KS_OTP_OER_Canceled = 'c'
# 执行成功
KS_OTP_OER_OK = '0'
# 期权持仓不够
KS_OTP_OER_NoPosition = '1'
# 资金不够
KS_OTP_OER_NoDeposit = '2'
# 会员不存在
KS_OTP_OER_NoParticipant = '3'
# 客户不存在
KS_OTP_OER_NoClient = '4'
# 合约不存在
KS_OTP_OER_NoInstrument = '6'
# 没有执行权限
KS_OTP_OER_NoRight = '7'
# 不合理的数量
KS_OTP_OER_InvalidVolume = '8'
# 没有足够的历史成交
KS_OTP_OER_NoEnoughHistoryTrade = '9'
# 未知
KS_OTP_OER_Unknown = 'a'

# typedef char TKSOTPExecResultType;

# -----------------------------------------------------
# TKSOTPBranchIDType是一个营业部编号类型
# -----------------------------------------------------
# typedef char TKSOTPBranchIDType[9];

# -----------------------------------------------------
# TKSOTPInvestorRangeType是一个投资者范围类型
# -----------------------------------------------------
# 所有
KS_OTP_IR_All = '1'
# 投资者组
KS_OTP_IR_Group = '2'
# 单一投资者
KS_OTP_IR_Single = '3'


