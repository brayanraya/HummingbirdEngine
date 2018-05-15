/* irrKlang.h -- interface of the 'irrKlang' library

  Copyright (C) 2002-2014 Nikolaus Gebhardt

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.
*/

#ifndef __IRR_KLANG_H_INCLUDED__
#define __IRR_KLANG_H_INCLUDED__

#include "ik_irrKlangTypes.h"
#include "ik_vec3d.h"

#include "ik_IRefCounted.h"
#include "ik_IVirtualRefCounted.h"

#include "ik_ESoundOutputDrivers.h"
#include "ik_ESoundEngineOptions.h"
#include "ik_EStreamModes.h"
#include "ik_SAudioStreamFormat.h"
#include "ik_ISoundEngine.h"
#include "ik_ISoundSource.h"
#include "ik_ISound.h"
#include "ik_IAudioStream.h"
#include "ik_IAudioStreamLoader.h"
#include "ik_ISoundEffectControl.h"
#include "ik_ISoundStopEventReceiver.h"
#include "ik_IFileFactory.h"
#include "ik_IFileReader.h"
#include "ik_ISoundDeviceList.h"
#include "ik_IAudioRecorder.h"
#include "ik_ISoundMixedOutputReceiver.h"

//! irrKlang Version
#define IRR_KLANG_VERSION "1.5.0"

#if defined(IRRKLANG_STATIC)
    #define IRRKLANG_API
#else
    #if (defined(WIN32) || defined(WIN64) || defined(_MSC_VER))
        #ifdef IRRKLANG_EXPORTS
        #define IRRKLANG_API __declspec(dllexport)
        #else
        #define IRRKLANG_API __declspec(dllimport)
        #endif // IRRKLANG_EXPORT
    #else
        #define IRRKLANG_API __attribute__((visibility("default")))
    #endif // defined(WIN32) || defined(WIN64)
#endif // IRRKLANG_STATIC

#if defined(_STDCALL_SUPPORTED)
#define IRRKLANGCALLCONV __stdcall  // Declare the calling convention.
#else
#define IRRKLANGCALLCONV
#endif // STDCALL_SUPPORTED

//! Everything in the irrKlang Sound Engine can be found in this namespace.
namespace irrklang
{
	//! Creates an irrKlang device. The irrKlang device is the root object for using the sound engine.
	/** \param driver The sound output driver to be used for sound output. Use irrklang::ESOD_AUTO_DETECT
	to let irrKlang decide which driver will be best.
	\param options A combination of irrklang::E_SOUND_ENGINE_OPTIONS literals. Default value is 
	irrklang::ESEO_DEFAULT_OPTIONS.
	\param deviceID Some additional optional deviceID for the audio driver. If not needed, simple
	set this to 0. 
	This can be used for example to set a specific ALSA output pcm device for output
	("default" or "hw", for example). For most driver types, available deviceIDs can be 
	enumerated using createSoundDeviceList().
	See @ref enumeratingDevices for an example or ISoundDeviceList or details.
	\param sdk_version_do_not_use Don't use or change this parameter. Always set it to
	IRRKLANG_SDK_VERSION, which is done by default. This is needed for sdk version checks.
	\return Returns pointer to the created irrKlang device or null if the
	device could not be created. If you don't need the device, use ISoundEngine::drop() to
	delete it. See IRefCounted::drop() for details.
	*/
	IRRKLANG_API ISoundEngine* IRRKLANGCALLCONV createIrrKlangDevice(
		E_SOUND_OUTPUT_DRIVER driver = ESOD_AUTO_DETECT,
		int options = ESEO_DEFAULT_OPTIONS,
		const char* deviceID = 0,
		const char* sdk_version_do_not_use = IRR_KLANG_VERSION);


	//! Creates a list of available sound devices for the driver type. 
	/** The device IDs in this list can be used as parameter to createIrrKlangDevice() to
	make irrKlang use a special sound device. See @ref enumeratingDevices for an example on how
	to use this.
	\param driver The sound output driver of which the list is generated. Set it irrklang::ESOD_AUTO_DETECT
	to let this function use the same device as createIrrKlangDevice() would choose.
	\param sdk_version_do_not_use Don't use or change this parameter. Always set it to
	IRRKLANG_SDK_VERSION, which is done by default. This is needed for sdk version checks.
	\return Returns a pointer to the list of enumerated sound devices for the selected sound driver.
	The device IDs in this list can be used as parameter to createIrrKlangDevice() to
	make irrKlang use a special sound device. 
	After you don't need the list anymore, call ISoundDeviceList::drop() in order to free its memory. */
	IRRKLANG_API ISoundDeviceList* IRRKLANGCALLCONV createSoundDeviceList(
		E_SOUND_OUTPUT_DRIVER driver = ESOD_AUTO_DETECT,
		const char* sdk_version_do_not_use = IRR_KLANG_VERSION);


	//! Creates an irrKlang audio recording device. The IAudioRecorder is the root object for recording audio.
	/** If you want to play back recorded audio as well, create the ISoundEngine first using
	createIrrKlangDevice() and then the IAudioRecorder using createIrrKlangAudioRecorder(), where
	you set the ISoundEngine as first parameter. See @ref recordingAudio for an example on how to use this.
	Note: audio recording is a very new feature a still beta in irrKlang. It currently only works in Windows
	and with DirectSound (subject to change).
	\param irrKlangDeviceForPlayback A pointer to the already existing sound device used for playback
	of audio. Sound sources recorded with the IAudioRecorder will be added into that device so that
	they can be played back there.
	\param driver The sound output driver to be used for recording audio. Use irrklang::ESOD_AUTO_DETECT
	to let irrKlang decide which driver will be best.
	\param deviceID Some additional optional deviceID for the audio driver. If not needed, simple
	set this to 0. Use createAudioRecorderDeviceList() to get a list of all deviceIDs.
	\param sdk_version_do_not_use Don't use or change this parameter. Always set it to
	IRRKLANG_SDK_VERSION, which is done by default. This is needed for sdk version checks.
	\return Returns pointer to the created irrKlang device or null if the
	device could not be created. If you don't need the device, use ISoundEngine::drop() to
	delete it. See IRefCounted::drop() for details.
	*/
	IRRKLANG_API IAudioRecorder* IRRKLANGCALLCONV createIrrKlangAudioRecorder(
		ISoundEngine* irrKlangDeviceForPlayback,
		E_SOUND_OUTPUT_DRIVER driver = ESOD_AUTO_DETECT,
		const char* deviceID = 0,
		const char* sdk_version_do_not_use = IRR_KLANG_VERSION);

	//! Creates a list of available recording devices for the driver type. 
	/** The device IDs in this list can be used as parameter to createIrrKlangAudioRecorder() to
	make irrKlang use a special recording device. 
	\param driver The sound output driver of which the list is generated. Set it irrklang::ESOD_AUTO_DETECT
	to let this function use the same device as createIrrKlangDevice() would choose.
	\param sdk_version_do_not_use Don't use or change this parameter. Always set it to
	IRRKLANG_SDK_VERSION, which is done by default. This is needed for sdk version checks.
	\return Returns a pointer to the list of enumerated recording devices for the selected sound driver.
	The device IDs in this list can be used as parameter to createIrrKlangAudioRecorder() to
	make irrKlang use a special sound device. 
	After you don't need the list anymore, call ISoundDeviceList::drop() in order to free its memory. */
	IRRKLANG_API ISoundDeviceList* IRRKLANGCALLCONV createAudioRecorderDeviceList(
		E_SOUND_OUTPUT_DRIVER driver = ESOD_AUTO_DETECT,
		const char* sdk_version_do_not_use = IRR_KLANG_VERSION);


	//! Converts a wchar_t string to an utf8 string, useful when using Windows in unicode mode. 
	/** irrKlang works with unicode file names, and accepts char* strings as parameters for names and filenames.
	If you are running irrKlang in Windows, and working with wchar_t* pointers instead of char* ones, 
	you can use this function to create a char* (UTF8) representation of your wchar_t* (UTF16) string.
	Works for filenames and other strings.
	\param pInputString zero terminated input string.
	\param pOutputBuffer the buffer where the converted string is written to. Be sure that this buffer
	has a big enough size. A good size would be three times the string length of your input buffer, like
	wcslen(yourInputBuffer)*3. Because each wchar_t can be represented by up to 3 chars.
	\param outputBufferSize size of your output buffer.
	\return Returns true if successful, and false if not. If 'false' is returned, maybe your buffer was too small. */
	IRRKLANG_API bool IRRKLANGCALLCONV makeUTF8fromUTF16string(
		const wchar_t* pInputString, char* pOutputBuffer, int outputBufferSize);


} // end namespace irrklang


/*! \file irrKlang.h
    \brief Main header file of the irrKlang sound library, the only file needed to include.
*/

#endif

