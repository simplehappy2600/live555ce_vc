#include "H264LiveFramedSource.hh"

//#include "H264LiveFramedSource.hh"
#include "InputFile.hh"
#include "GroupsockHelper.hh"

////////// H264LiveFramedSource //////////

H264LiveFramedSource* H264LiveFramedSource::createNew(UsageEnvironment& env, char const* channel){
	return new H264LiveFramedSource(env, channel);
}

H264LiveFramedSource::H264LiveFramedSource(UsageEnvironment& env, char const* channel) : FramedSource(env){
	char * fileName = "akiyo_qcif.264.len";
	
	this->fid = OpenInputFile(env, fileName);
	if (this->fid != NULL){
		this->envir() << "\nopen file " << fileName << " ok";
	}
	else{
		this->envir() << "\nopen file " << fileName << " fail";
	}
}

H264LiveFramedSource::~H264LiveFramedSource() {
	this->envir() << "\nclose file ";
	if (fid == NULL){
		return;
	}
	CloseInputFile(fid);
}

void H264LiveFramedSource::doGetNextFrame() {

lbl_start:
	//doReadFromFile();
	int frameSize;
	
	fread(&frameSize, sizeof(int), 1, fid);

	this->envir() << "\nread frameSize: " << frameSize;

	int ret = fread(fTo, frameSize, 1, fid);
	if (ret == 0){
		fseek(fid, 0, SEEK_SET);
		goto lbl_start;
	}

	fMaxSize = fFrameSize = frameSize;	

	gettimeofday(&fPresentationTime, NULL);

	nextTask() = envir().taskScheduler().scheduleDelayedTask(0, (TaskFunc*)FramedSource::afterGetting, this);
}



//void H264LiveFramedSource::doStopGettingFrames() {
//#ifndef READ_FROM_FILES_SYNCHRONOUSLY
//  envir().taskScheduler().turnOffBackgroundReadHandling(fileno(fFid));
//  fHaveStartedReading = False;
//#endif
//}

//void H264LiveFramedSource::fileReadableHandler(H264LiveFramedSource* source, int /*mask*/) {
//  if (!source->isCurrentlyAwaitingData()) {
//    source->doStopGettingFrames(); // we're not ready for the data yet
//    return;
//  }
//  source->doReadFromFile();
//}

//static Boolean const readFromFilesSynchronously
//#ifdef READ_FROM_FILES_SYNCHRONOUSLY
//= True;
//#else
//= False;
//#endif

//void H264LiveFramedSource::doReadFromFile() {
//  // Try to read as many bytes as will fit in the buffer provided (or "fPreferredFrameSize" if less)
//  if (fLimitNumBytesToStream && fNumBytesToStream < (u_int64_t)fMaxSize) {
//    fMaxSize = (unsigned)fNumBytesToStream;
//  }
//  if (fPreferredFrameSize > 0 && fPreferredFrameSize < fMaxSize) {
//    fMaxSize = fPreferredFrameSize;
//  }
//  if (readFromFilesSynchronously || fFidIsSeekable) {
//    fFrameSize = fread(fTo, 1, fMaxSize, fFid);
//  } else {
//    // For non-seekable files (e.g., pipes), call "read()" rather than "fread()", to ensure that the read doesn't block:
//    fFrameSize = read(fileno(fFid), fTo, fMaxSize);
//  }
//  if (fFrameSize == 0) {
//    handleClosure(this);
//    return;
//  }
//  fNumBytesToStream -= fFrameSize;
//
//  // Set the 'presentation time':
//  if (fPlayTimePerFrame > 0 && fPreferredFrameSize > 0) {
//    if (fPresentationTime.tv_sec == 0 && fPresentationTime.tv_usec == 0) {
//      // This is the first frame, so use the current time:
//      gettimeofday(&fPresentationTime, NULL);
//    } else {
//      // Increment by the play time of the previous data:
//      unsigned uSeconds	= fPresentationTime.tv_usec + fLastPlayTime;
//      fPresentationTime.tv_sec += uSeconds/1000000;
//      fPresentationTime.tv_usec = uSeconds%1000000;
//    }
//
//    // Remember the play time of this data:
//    fLastPlayTime = (fPlayTimePerFrame*fFrameSize)/fPreferredFrameSize;
//    fDurationInMicroseconds = fLastPlayTime;
//  } else {
//    // We don't know a specific play time duration for this data,
//    // so just record the current time as being the 'presentation time':
//    gettimeofday(&fPresentationTime, NULL);
//  }
//
//  // Inform the reader that he has data:
//#ifdef READ_FROM_FILES_SYNCHRONOUSLY
//  // To avoid possible infinite recursion, we need to return to the event loop to do this:
//  nextTask() = envir().taskScheduler().scheduleDelayedTask(0,
//				(TaskFunc*)FramedSource::afterGetting, this);
//#else
//  // Because the file read was done from the event loop, we can call the
//  // 'after getting' function directly, without risk of infinite recursion:
//  FramedSource::afterGetting(this);
//#endif
//}
