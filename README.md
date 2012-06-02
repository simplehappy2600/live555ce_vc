live555  vc2008
=========

modified based on live.2012.02.29.tar.gz
vs2008编译

工程文件在build目录

	testOnDemandRTSPServer_ce, 编译wince程序
	testOnDemandRTSPServer_vc_264, 编译VC程序, 用文件模拟264流

修改list:

	ByteStreamFileSource.cpp wince读文件
	MediaSession.cpp 宏定义，只支持264
	RTSPServerSupportingHTTPStreaming.cpp
	DynamicRTSPServer.cpp
	live555MediaServer.cpp
	testOnDemandRTSPServer.cpp 支持.264文件, 增加模拟264流H264VideoLiveServerMediaSubsession
	UsageEnvironment.cpp

增加文件
	
	build/ce wince编译需要文件
	build/src 模拟264实时流文件, 目前实现从文件中重读读, 可修改为从264编码器获取流数据

修改后也可将mediaServer/live555MediaServer编译成wince版本


