/*****************************************************************//**
 * \file	MackieControl.cpp
 * \brief	A compact Mackie Control library on JUCE.
 * 
 * \author	WuChang
 * \email	31423836@qq.com
 * \date	July 2023
 * \version	1.0.2
 * \license	MIT License
 *********************************************************************/

#include "MackieControl.h"

namespace mackieControl {
	constinit auto validSysExMessage = std::to_array({
		SysExMessage::DeviceQuery,
		SysExMessage::HostConnectionQuery,
		SysExMessage::HostConnectionReply,
		SysExMessage::HostConnectionConfirmation,
		SysExMessage::HostConnectionError,
		SysExMessage::LCDBackLightSaver,
		SysExMessage::TouchlessMovableFaders,
		SysExMessage::FaderTouchSensitivity,
		SysExMessage::GoOffline,
		SysExMessage::TimeCodeBBTDisplay,
		SysExMessage::Assignment7SegmentDisplay,
		SysExMessage::LCD,
		SysExMessage::VersionRequest,
		SysExMessage::VersionReply,
		SysExMessage::ChannelMeterMode,
		SysExMessage::GlobalLCDMeterMode,
		SysExMessage::AllFaderstoMinimum,
		SysExMessage::AllLEDsOff,
		SysExMessage::Reset
		});
	constexpr bool isValidSysExMessage(SysExMessage mes) {
		return std::find(validSysExMessage.begin(), validSysExMessage.end(), mes) != validSysExMessage.end();
	}
	constexpr bool isValidSysExMessage(int mes) {
		return isValidSysExMessage(static_cast<SysExMessage>(mes));
	}

	constinit auto validVelocityMessage = std::to_array({
		VelocityMessage::Off,
		VelocityMessage::Flashing,
		VelocityMessage::On
		});
	constexpr bool isValidVelocityMessage(VelocityMessage mes) {
		return std::find(validVelocityMessage.begin(), validVelocityMessage.end(), mes) != validVelocityMessage.end();
	}
	constexpr bool isValidVelocityMessage(int mes) {
		return isValidVelocityMessage(static_cast<VelocityMessage>(mes));
	}

	constinit auto validNoteMessage = std::to_array({
		NoteMessage::RECRDYCh1, NoteMessage::RECRDYCh2, NoteMessage::RECRDYCh3, NoteMessage::RECRDYCh4,
		NoteMessage::RECRDYCh5, NoteMessage::RECRDYCh6, NoteMessage::RECRDYCh7, NoteMessage::RECRDYCh8,
		NoteMessage::SOLOCh1, NoteMessage::SOLOCh2, NoteMessage::SOLOCh3, NoteMessage::SOLOCh4,
		NoteMessage::SOLOCh5, NoteMessage::SOLOCh6, NoteMessage::SOLOCh7, NoteMessage::SOLOCh8,
		NoteMessage::MUTECh1, NoteMessage::MUTECh2, NoteMessage::MUTECh3, NoteMessage::MUTECh4,
		NoteMessage::MUTECh5, NoteMessage::MUTECh6, NoteMessage::MUTECh7, NoteMessage::MUTECh8,
		NoteMessage::SELECTCh1, NoteMessage::SELECTCh2, NoteMessage::SELECTCh3, NoteMessage::SELECTCh4,
		NoteMessage::SELECTCh5, NoteMessage::SELECTCh6, NoteMessage::SELECTCh7, NoteMessage::SELECTCh8,
		NoteMessage::VSelectCh1, NoteMessage::VSelectCh2, NoteMessage::VSelectCh3, NoteMessage::VSelectCh4,
		NoteMessage::VSelectCh5, NoteMessage::VSelectCh6, NoteMessage::VSelectCh7, NoteMessage::VSelectCh8,
		NoteMessage::ASSIGNMENTTRACK, NoteMessage::ASSIGNMENTSEND, NoteMessage::ASSIGNMENTPANSURROUND,
		NoteMessage::ASSIGNMENTPLUGIN, NoteMessage::ASSIGNMENTEQ, NoteMessage::ASSIGNMENTINSTRUMENT,
		NoteMessage::FADERBANKSBANKLeft, NoteMessage::FADERBANKSBANKRight,
		NoteMessage::FADERBANKSCHANNELLeft, NoteMessage::FADERBANKSCHANNELRight,
		NoteMessage::FLIP,
		NoteMessage::GLOBALVIEW,
		NoteMessage::NAMEVALUE,
		NoteMessage::SMPTEBEATS,
		NoteMessage::Function1, NoteMessage::Function2, NoteMessage::Function3, NoteMessage::Function4,
		NoteMessage::Function5, NoteMessage::Function6, NoteMessage::Function7, NoteMessage::Function8,
		NoteMessage::GLOBALVIEWMIDITRACKS, NoteMessage::GLOBALVIEWINPUTS,
		NoteMessage::GLOBALVIEWAUDIOTRACKS, NoteMessage::GLOBALVIEWAUDIOINSTRUMENT,
		NoteMessage::GLOBALVIEWAUX, NoteMessage::GLOBALVIEWBUSSES,
		NoteMessage::GLOBALVIEWOUTPUTS, NoteMessage::GLOBALVIEWUSER,
		NoteMessage::SHIFT, NoteMessage::OPTION, NoteMessage::CONTROL, NoteMessage::CMDALT,
		NoteMessage::AUTOMATIONREADOFF, NoteMessage::AUTOMATIONWRITE, NoteMessage::AUTOMATIONTRIM,
		NoteMessage::AUTOMATIONTOUCH, NoteMessage::AUTOMATIONLATCH,
		NoteMessage::GROUP,
		NoteMessage::UTILITIESSAVE, NoteMessage::UTILITIESUNDO,
		NoteMessage::UTILITIESCANCEL, NoteMessage::UTILITIESENTER,
		NoteMessage::MARKER,
		NoteMessage::NUDGE,
		NoteMessage::CYCLE,
		NoteMessage::DROP,
		NoteMessage::REPLACE,
		NoteMessage::CLICK,
		NoteMessage::SOLO,
		NoteMessage::REWIND, NoteMessage::FASTFWD, NoteMessage::STOP, NoteMessage::PLAY, NoteMessage::RECORD,
		NoteMessage::CursorUp, NoteMessage::CursorDown, NoteMessage::CursorLeft, NoteMessage::CursorRight,
		NoteMessage::Zoom,
		NoteMessage::Scrub,
		NoteMessage::UserSwitchA, NoteMessage::UserSwitchB,
		NoteMessage::FaderTouchCh1, NoteMessage::FaderTouchCh2,
		NoteMessage::FaderTouchCh3, NoteMessage::FaderTouchCh4,
		NoteMessage::FaderTouchCh5, NoteMessage::FaderTouchCh6,
		NoteMessage::FaderTouchCh7, NoteMessage::FaderTouchCh8,
		NoteMessage::FaderTouchMaster,
		NoteMessage::SMPTELED,
		NoteMessage::BEATSLED,
		NoteMessage::RUDESOLOLIGHT,
		NoteMessage::Relayclick
		});
	constexpr bool isValidNoteMessage(NoteMessage mes) {
		return std::find(validNoteMessage.begin(), validNoteMessage.end(), mes) != validNoteMessage.end();
	}
	constexpr bool isValidNoteMessage(int mes) {
		return isValidNoteMessage(static_cast<NoteMessage>(mes));
	}

	constinit auto validCCMessage = std::to_array({
		CCMessage::VPot1, CCMessage::VPot2, CCMessage::VPot3, CCMessage::VPot4,
		CCMessage::VPot5, CCMessage::VPot6, CCMessage::VPot7, CCMessage::VPot8,
		CCMessage::ExternalController,
		CCMessage::VPotLEDRing1, CCMessage::VPotLEDRing2, CCMessage::VPotLEDRing3, CCMessage::VPotLEDRing4,
		CCMessage::VPotLEDRing5, CCMessage::VPotLEDRing6, CCMessage::VPotLEDRing7, CCMessage::VPotLEDRing8,
		CCMessage::JogWheel,
		CCMessage::TimeCodeBBTDisplay1, CCMessage::TimeCodeBBTDisplay2,
		CCMessage::TimeCodeBBTDisplay3, CCMessage::TimeCodeBBTDisplay4,
		CCMessage::TimeCodeBBTDisplay5, CCMessage::TimeCodeBBTDisplay6,
		CCMessage::TimeCodeBBTDisplay7, CCMessage::TimeCodeBBTDisplay8,
		CCMessage::TimeCodeBBTDisplay9, CCMessage::TimeCodeBBTDisplay10,
		CCMessage::Assignment7SegmentDisplay1, CCMessage::Assignment7SegmentDisplay2,
		CCMessage::Assignment7SegmentDisplay3
		});
	constexpr bool isValidCCMessage(CCMessage mes) {
		return std::find(validCCMessage.begin(), validCCMessage.end(), mes) != validCCMessage.end();
	}
	constexpr bool isValidCCMessage(int mes) {
		return isValidCCMessage(static_cast<CCMessage>(mes));
	}

	Message::Message(const MidiMessage& midiMessage)
		: message(midiMessage) {}

	Message::Message(const Message& message) 
		: message(message.message) {}

	Message::Message(Message&& message) noexcept
		: message(std::move(message.message)) {}

	Message& Message::operator=(const Message& message) {
		if (this != &message) {
			this->message = message.message;
		}
		return *this;
	}

	Message& Message::operator=(Message&& message) noexcept {
		if (this != &message) {
			this->message = std::move(message.message);
		}
		return *this;
	}

	Message& Message::operator=(const MidiMessage& message) {
		this->message = message;
		return *this;
	}

	MidiMessage Message::toMidi() const {
		return this->message;
	}

	bool Message::isSysEx() const {
		if (message.isSysEx()) {
			if (this->message.getSysExDataSize() >= 5) {
				auto ptrData = this->message.getSysExData();
				return isValidSysExMessage(ptrData[4]);
			}
		}
		return false;
	}

	bool Message::isNote() const {
		if (this->message.isNoteOnOrOff()) {
			return isValidNoteMessage(this->message.getNoteNumber()) &&
				isValidVelocityMessage(this->message.getVelocity());
		}
		return false;
	}

	bool Message::isCC() const {
		if (this->message.isController()) {
			return isValidCCMessage(this->message.getControllerNumber());
		}
		return false;
	}

	bool Message::isPitchWheel() const {
		if (this->message.isPitchWheel()) {
			auto channel = this->message.getChannel();
			return channel >= 1 && channel <= 9;
		}
		return false;
	}

	bool Message::isChannelPressure() const {
		if (this->message.isChannelPressure()) {
			return true;
		}
		return false;
	}

	bool Message::isMackieControl() const {
		return this->isSysEx() ||
			this->isNote() ||
			this->isCC() ||
			this->isPitchWheel() ||
			this->isChannelPressure();
	}

	std::tuple<SysExMessage> Message::getSysExData() const {
		if (this->message.getSysExDataSize() < 5) { return { static_cast<SysExMessage>(-1) }; }
		return { static_cast<SysExMessage>(this->message.getSysExData()[4]) };
	}

	std::tuple<std::array<uint8_t, 7>, uint32_t> Message::getHostConnectionQueryData() const {
		if (this->message.getSysExDataSize() <
			5 + sizeof(std::array<uint8_t, 7>) + sizeof(uint32_t)) { return std::tuple<std::array<uint8_t, 7>, uint32_t>{}; }

		std::array<uint8_t, 7> bytes;
		std::memcpy(bytes.data(), &(this->message.getSysExData()[5]), sizeof(bytes));

		return { bytes, static_cast<uint32_t>(this->message.getSysExData()[5 + sizeof(bytes)]) };
	}

	std::tuple<std::array<uint8_t, 7>, uint32_t> Message::getHostConnectionReplyData() const {
		if (this->message.getSysExDataSize() <
			5 + sizeof(std::array<uint8_t, 7>) + sizeof(uint32_t)) {
			return std::tuple<std::array<uint8_t, 7>, uint32_t>{};
		}

		std::array<uint8_t, 7> bytes;
		std::memcpy(bytes.data(), &(this->message.getSysExData()[5]), sizeof(bytes));

		return { bytes, static_cast<uint32_t>(this->message.getSysExData()[5 + sizeof(bytes)]) };
	}

	std::tuple<std::array<uint8_t, 7>> Message::getHostConnectionConfirmationData() const {
		if (this->message.getSysExDataSize() < 5 + sizeof(std::array<uint8_t, 7>)) {
			return std::tuple<std::array<uint8_t, 7>>{};
		}

		std::array<uint8_t, 7> bytes;
		std::memcpy(bytes.data(), &(this->message.getSysExData()[5]), sizeof(bytes));

		return { bytes };
	}

	std::tuple<std::array<uint8_t, 7>> Message::getHostConnectionErrorData() const {
		if (this->message.getSysExDataSize() < 5 + sizeof(std::array<uint8_t, 7>)) {
			return std::tuple<std::array<uint8_t, 7>>{};
		}

		std::array<uint8_t, 7> bytes;
		std::memcpy(bytes.data(), &(this->message.getSysExData()[5]), sizeof(bytes));

		return { bytes };
	}

	std::tuple<uint8_t, uint8_t> Message::getLCDBackLightSaverData() const {
		if (this->message.getSysExDataSize() < 5 + 1) {
			return std::tuple<uint8_t, uint8_t>{};
		}

		return { static_cast<uint8_t>(this->message.getSysExData()[5]),
			(this->message.getSysExDataSize() >= 7) ? static_cast<uint8_t>(this->message.getSysExData()[6]) : 0 };
	}

	std::tuple<uint8_t> Message::getTouchlessMovableFadersData() const {
		if (this->message.getSysExDataSize() < 5 + 1) {
			return std::tuple<uint8_t>{};
		}

		return { static_cast<uint8_t>(this->message.getSysExData()[5]) };
	}

	std::tuple<uint8_t, uint8_t> Message::getFaderTouchSensitivityData() const {
		if (this->message.getSysExDataSize() < 5 + 2) {
			return std::tuple<uint8_t, uint8_t>{};
		}

		return { static_cast<uint8_t>(this->message.getSysExData()[5]),
			static_cast<uint8_t>(this->message.getSysExData()[6]) };
	}

	std::tuple<const uint8_t*, int> Message::getTimeCodeBBTDisplayData() const {
		if (this->message.getSysExDataSize() < 5 + 1 + 1 + 1) {
			return std::tuple<uint8_t*, int>{};
		}

		return { &(this->message.getSysExData()[6]),
			this->message.getSysExDataSize() - 1 - 6 };
	}

	std::tuple<std::array<uint8_t, 2>> Message::getAssignment7SegmentDisplayData() const {
		if (this->message.getSysExDataSize() < 5 + 1 + sizeof(std::array<uint8_t, 2>)) {
			return std::tuple<std::array<uint8_t, 2>>{};
		}

		std::array<uint8_t, 2> bytes;
		std::memcpy(bytes.data(), &(this->message.getSysExData()[6]), sizeof(bytes));

		return { bytes };
	}

	std::tuple<uint8_t, const char*, int> Message::getLCDData() const {
		if (this->message.getSysExDataSize() < 5 + 1 + 1) {
			return std::tuple<uint8_t, char*, int>{};
		}

		return { static_cast<uint8_t>(this->message.getSysExData()[5]),
			reinterpret_cast<const char*>(&(this->message.getSysExData()[6])) ,
			this->message.getSysExDataSize() - 6 };
	}

	std::tuple<const char*, int> Message::getVersionReplyData() const {
		if (this->message.getSysExDataSize() < 5 + 1 + 1) {
			return std::tuple<char*, int>{};
		}

		return { reinterpret_cast<const char*>(&(this->message.getSysExData()[6])) ,
			this->message.getSysExDataSize() - 6 };
	}

	std::tuple<uint8_t, uint8_t> Message::getChannelMeterModeData() const {
		if (this->message.getSysExDataSize() < 5 + 2) {
			return std::tuple<uint8_t, uint8_t>{};
		}

		return { static_cast<uint8_t>(this->message.getSysExData()[5]),
			static_cast<uint8_t>(this->message.getSysExData()[6]) };
	}

	std::tuple<uint8_t> Message::getGlobalLCDMeterModeData() const {
		if (this->message.getSysExDataSize() < 5 + 1) {
			return std::tuple<uint8_t>{};
		}

		return { static_cast<uint8_t>(this->message.getSysExData()[5]) };
	}

	std::tuple<NoteMessage, VelocityMessage> Message::getNoteData() const {
		return { static_cast<NoteMessage>(this->message.getNoteNumber()),
			static_cast<VelocityMessage>(this->message.getVelocity()) };
	}

	std::tuple<CCMessage, int> Message::getCCData() const {
		return { static_cast<CCMessage>(this->message.getControllerNumber()),
			this->message.getControllerValue() };
	}

	std::tuple<int, int> Message::getPitchWheelData() const {
		return { this->message.getChannel(),
			this->message.getPitchWheelValue() };
	}

	std::tuple<int, int> Message::getChannelPressureData() const {
		int value = this->message.getChannelPressureValue();
		return { value / 16 + 1,value % 16 };
	}

	Message Message::fromMidi(const MidiMessage& message) {
		return Message{ message };
	}

	MidiMessage Message::toMidi(const Message& message) {
		return message.toMidi();
	}

	Message Message::createDeviceQuery() {
		uint8_t bytes[5] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::DeviceQuery);

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createHostConnectionQuery(const std::array<uint8_t, 7>& serialNum, uint32_t challengeCode) {
		uint8_t bytes[5 + sizeof(serialNum) + sizeof(challengeCode)] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::HostConnectionQuery);
		std::memcpy(&bytes[5], serialNum.data(), sizeof(serialNum));
		std::memcpy(&bytes[5 + sizeof(serialNum)], &challengeCode, sizeof(challengeCode));

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createHostConnectionReply(const std::array<uint8_t, 7>& serialNum, uint32_t responseCode) {
		uint8_t bytes[5 + sizeof(serialNum) + sizeof(responseCode)] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::HostConnectionReply);
		std::memcpy(&bytes[5], serialNum.data(), sizeof(serialNum));
		std::memcpy(&bytes[5 + sizeof(serialNum)], &responseCode, sizeof(responseCode));

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createHostConnectionConfirmation(const std::array<uint8_t, 7>& serialNum) {
		uint8_t bytes[5 + sizeof(serialNum)] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::HostConnectionConfirmation);
		std::memcpy(&bytes[5], serialNum.data(), sizeof(serialNum));

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createHostConnectionError(const std::array<uint8_t, 7>& serialNum) {
		uint8_t bytes[5 + sizeof(serialNum)] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::HostConnectionError);
		std::memcpy(&bytes[5], serialNum.data(), sizeof(serialNum));

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createLCDBackLightSaver(uint8_t state, uint8_t timeout) {
		if (state > 0) {
			uint8_t bytes[5 + 2] = {};
			bytes[4] = static_cast<uint8_t>(SysExMessage::LCDBackLightSaver);
			bytes[5] = state;
			bytes[6] = timeout;

			return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
		}
		
		uint8_t bytes[5 + 1] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::LCDBackLightSaver);
		bytes[5] = state;

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createTouchlessMovableFaders(uint8_t state) {
		uint8_t bytes[5 + 1] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::TouchlessMovableFaders);
		bytes[5] = state;

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createFaderTouchSensitivity(uint8_t channelNumber, uint8_t value) {
		uint8_t bytes[5 + 2] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::FaderTouchSensitivity);
		bytes[5] = channelNumber;
		bytes[6] = value;

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createGoOffline() {
		uint8_t bytes[5] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::GoOffline);

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createTimeCodeBBTDisplay(const uint8_t* data, int size) {
		int byteSize = 5 + 1 + size + 1;
		auto bytes = std::unique_ptr<uint8_t[]>(new uint8_t[byteSize]());

		bytes[4] = static_cast<uint8_t>(SysExMessage::TimeCodeBBTDisplay);
		std::memcpy(&bytes[6], data, size);

		return Message{ MidiMessage::createSysExMessage(bytes.get(), byteSize) };
	}

	Message Message::createAssignment7SegmentDisplay(const std::array<uint8_t, 2>& data) {
		uint8_t bytes[5 + 1 + sizeof(data)] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::Assignment7SegmentDisplay);
		std::memcpy(&bytes[6], data.data(), sizeof(data));

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createLCD(uint8_t place, const char* data, int size) {
		int byteSize = 5 + 1 + size;
		auto bytes = std::unique_ptr<uint8_t[]>(new uint8_t[byteSize]());

		bytes[4] = static_cast<uint8_t>(SysExMessage::LCD);
		bytes[5] = place;
		std::memcpy(&bytes[6], data, size);

		return Message{ MidiMessage::createSysExMessage(bytes.get(), byteSize) };
	}

	Message Message::createVersionRequest() {
		uint8_t bytes[5] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::VersionRequest);

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createVersionReply(const char* data, int size) {
		int byteSize = 5 + 1 + size;
		auto bytes = std::unique_ptr<uint8_t[]>(new uint8_t[byteSize]());

		bytes[4] = static_cast<uint8_t>(SysExMessage::VersionReply);
		std::memcpy(&bytes[6], data, size);

		return Message{ MidiMessage::createSysExMessage(bytes.get(), byteSize) };
	}

	Message Message::createChannelMeterMode(uint8_t channelNumber, uint8_t mode) {
		uint8_t bytes[5 + 2] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::ChannelMeterMode);
		bytes[5] = channelNumber;
		bytes[6] = mode;

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createGlobalLCDMeterMode(uint8_t mode) {
		uint8_t bytes[5 + 1] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::GlobalLCDMeterMode);
		bytes[5] = mode;

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createAllFaderstoMinimum() {
		uint8_t bytes[5] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::AllFaderstoMinimum);

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createAllLEDsOff() {
		uint8_t bytes[5] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::AllLEDsOff);

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createReset() {
		uint8_t bytes[5] = {};
		bytes[4] = static_cast<uint8_t>(SysExMessage::Reset);

		return Message{ MidiMessage::createSysExMessage(bytes, sizeof(bytes)) };
	}

	Message Message::createNote(NoteMessage type, VelocityMessage vel) {
		return Message{ MidiMessage::noteOn(1, static_cast<int>(type), static_cast<uint8_t>(vel)) };
	}

	Message Message::createCC(CCMessage type, int value) {
		return Message{ MidiMessage::controllerEvent(1, static_cast<int>(type), static_cast<int>(value)) };
	}

	Message Message::createPitchWheel(int channel, int value) {
		return Message{ MidiMessage::pitchWheel(channel, value) };
	}

	Message Message::createChannelPressure(int channel, int value) {
		return Message{ MidiMessage::channelPressureChange(1, (channel - 1) * 16 + value) };
	}

	uint8_t Message::charToMackie(char c) {
		if (c >= 'a' && c <= 'z') { return (c - 'a') + 1; }
		else if (c >= 'A' && c <= 'Z') { return (c - 'A') + 1; }
		else if (c >= '0' && c <= '9') { return c; }

		return ' ';
	}

	char Message::mackieToChar(uint8_t c) {
		if ((c - 1) >= 0 && (c - 1) <= 'Z' - 'A') { return 'A' + (c - 1); }
		else if (c >= '0' && c <= '9') { return c; }

		return ' ';
	}

	uint8_t Message::toLCDPlace(bool lowerLine, uint8_t index) {
		return (lowerLine ? 56 : 0) + index;
	}

	uint8_t Message::toChannelMeterMode(
		bool signalLEDEnabled, bool peakHoldDisplayEnabled, bool LCDLevelMeterEnabled) {
		return (static_cast<uint8_t>(signalLEDEnabled) << 0)
			+ (static_cast<uint8_t>(peakHoldDisplayEnabled) << 1)
			+ (static_cast<uint8_t>(LCDLevelMeterEnabled) << 2);
	}

	int Message::toVPotValue(WheelType type, int ticks) {
		return static_cast<int>(type) * 64 + ticks;
	}

	int Message::toVPotLEDRingValue(bool centerLEDOn, VPotLEDRingMode mode, int value) {
		return static_cast<int>(centerLEDOn) * 64
			+ static_cast<int>(mode) * 16
			+ value;
	}

	int Message::toJogWheelValue(WheelType type, int ticks) {
		return static_cast<int>(type) * 64 + ticks;
	}

	std::tuple<bool, uint8_t> Message::convertLCDPlace(uint8_t place) {
		return { place >= 56, (place >= 56) ? (place - 56) : place };
	}

	std::tuple<bool, bool, bool> Message::convertChannelMeterMode(uint8_t mode) {
		return { mode & (1 << 0),
			mode & (1 << 1),
			mode & (1 << 2) };
	}

	std::tuple<WheelType, int> Message::convertVPotValue(int value) {
		return { static_cast<WheelType>(value / 64), value % 64 };
	}

	std::tuple<bool, VPotLEDRingMode, int> Message::convertVPotLEDRingValue(int value) {
		return { static_cast<bool>(value / 64), static_cast<VPotLEDRingMode>((value % 64) / 16), value % 16 };
	}

	std::tuple<WheelType, int> Message::convertJogWheelValue(int value) {
		return { static_cast<WheelType>(value / 64), value % 64 };
	}
}
