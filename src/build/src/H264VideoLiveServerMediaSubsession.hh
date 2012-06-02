#ifndef _FILE_H264VideoLiveServerMediaSubsession_hh
#define _FILE_H264VideoLiveServerMediaSubsession_hh

#include "OnDemandServerMediaSubsession.hh"
#include "H264LiveFramedSource.hh"

class H264VideoLiveServerMediaSubsession : public OnDemandServerMediaSubsession{
public:
  static H264VideoLiveServerMediaSubsession*
  createNew(UsageEnvironment& env, char const* channel, Boolean reuseFirstSource);

  // Used to implement "getAuxSDPLine()":
  void checkForAuxSDPLine1();
  void afterPlayingDummy1();

protected:
  H264VideoLiveServerMediaSubsession(UsageEnvironment& env,
				      char const* channel, Boolean reuseFirstSource);
      // called only by createNew();
  virtual ~H264VideoLiveServerMediaSubsession();

  void setDoneFlag() { fDoneFlag = ~0; }

protected: // redefined virtual functions
  virtual char const* getAuxSDPLine(RTPSink* rtpSink,
				    FramedSource* inputSource);
  virtual FramedSource* createNewStreamSource(unsigned clientSessionId,
					      unsigned& estBitrate);
  virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
                                    unsigned char rtpPayloadTypeIfDynamic,
				    FramedSource* inputSource);

private:
  char* fAuxSDPLine;
  char fDoneFlag; // used when setting up "fAuxSDPLine"
  RTPSink* fDummyRTPSink; // ditto

  char const*channel;
};

#endif