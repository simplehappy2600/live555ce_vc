#ifndef _FILE_H264LiveFramedSource_hh
#define _FILE_H264LiveFramedSource_hh

#include "FramedSource.hh"
#include <GroupsockHelper.hh>

#include "FramedFileSource.hh"

//class H264LiveFramedSource : public FramedSource {
class H264LiveFramedSource: public FramedSource {
public:
  static H264LiveFramedSource* createNew(UsageEnvironment& env, char const* channel);
  // "preferredFrameSize" == 0 means 'no preference'
  // "playTimePerFrame" is in microseconds

  //static H264LiveFramedSource* createNew(UsageEnvironment& env,
		//			 FILE* fid,
		//			 unsigned preferredFrameSize = 0,
		//			 unsigned playTimePerFrame = 0);
      // an alternative version of "createNew()" that's used if you already have
      // an open file.

  //u_int64_t fileSize() const { return fFileSize; }
      // 0 means zero-length, unbounded, or unknown

  //void seekToByteAbsolute(u_int64_t byteNumber, u_int64_t numBytesToStream = 0);
    // if "numBytesToStream" is >0, then we limit the stream to that number of bytes, before treating it as EOF
  //void seekToByteRelative(int64_t offset);
  //void seekToEnd(); // to force EOF handling on the next read

protected:
  H264LiveFramedSource(UsageEnvironment& env, char const* channel);

	// called only by createNew()

  virtual ~H264LiveFramedSource();

  //static void fileReadableHandler(ByteStreamFileSource* source, int mask);
  //void doReadFromFile();

private:
  // redefined virtual functions:
  virtual void doGetNextFrame();
  //virtual void doStopGettingFrames();

protected:
  //u_int64_t fFileSize;

private:
	FILE* fid;
  //unsigned fPreferredFrameSize;
  ////unsigned fPlayTimePerFrame;
  //Boolean fFidIsSeekable;
  //unsigned fLastPlayTime;
  //Boolean fHaveStartedReading;
  //Boolean fLimitNumBytesToStream;
  //u_int64_t fNumBytesToStream; // used iff "fLimitNumBytesToStream" is True
};

#endif