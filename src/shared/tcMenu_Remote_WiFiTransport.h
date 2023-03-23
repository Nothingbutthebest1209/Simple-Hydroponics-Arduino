/*  Hydruino: Simple automation controller for hydroponic grow systems.
    Copyright (C) 2022-2023 NachtRaveVL     <nachtravevl@gmail.com>
    tcMenu WiFi Remote Control
*/
#include <Hydruino.h>
#if defined(HYDRO_USE_WIFI) && defined(HYDRO_USE_GUI)

/*
 * Copyright (c) 2018 https://www.thecoderscorner.com (Dave Cherry).
 * This product is licensed under an Apache license, see the LICENSE file in the top-level directory.
 */

/* Changelist:
 * - Enclosed inside of #ifdef & reorg'ed for general inclusion
 * - Derived from EthernetTransport
 */

/**
 * @file tcMenu_Remote_WiFiTransport.h
 * 
 * WiFi remote capability plugin. This file is a plugin file and should not be directly edited,
 * it will be replaced each time the project is built. If you want to edit this file in place,
 * make sure to rename it first.
 */

#ifndef TCMENU_WIFITRANSPORT_H_
#define TCMENU_WIFITRANSPORT_H_

#include <RemoteConnector.h>
#include <RemoteAuthentication.h>
#include <tcUtil.h>
#include <remote/BaseRemoteComponents.h>

#ifndef WIFI_BUFFER_SIZE
#define WIFI_BUFFER_SIZE 64
#endif

#if WIFI_BUFFER_SIZE > 0
#include <remote/BaseBufferedRemoteTransport.h>
#endif

namespace tcremote {

#if WIFI_BUFFER_SIZE > 0

/**
 * An implementation of TagValueTransport that is able to read and write via a buffer to sockets.
 */
    class WiFiTagValTransport : public tcremote::BaseBufferedRemoteTransport {
    private:
        WiFiClient client;
    public:
        WiFiTagValTransport() : BaseBufferedRemoteTransport(BUFFER_MESSAGES_TILL_FULL, WIFI_BUFFER_SIZE, MAX_VALUE_LEN) { }
        ~WiFiTagValTransport() override = default;
        void setClient(WiFiClient cl) { this->client = cl; }

        int fillReadBuffer(uint8_t* data, int maxSize) override;
        void flush() override;
        bool available() override;
        bool connected() override;
        void close() override;
    };

#else // wifi buffering not needed

/**
 * An implementation of TagValueTransport that is able to read and write using sockets.
 */
class WiFiTagValTransport : public TagValueTransport {
private:
	WiFiClient client;
public:
	WiFiTagValTransport() : TagValueTransport(TagValueTransportType::TVAL_UNBUFFERED) {};
	~WiFiTagValTransport() override = default;
	void setClient(WiFiClient client) { this->client = client; }

	int writeChar(char data) override ;
	int writeStr(const char* data) override;
	void flush() override;
	bool available() override;
	bool connected() override;
	uint8_t readByte() override;
	bool readAvailable() override;
    void close() override;
};

#endif // wifi buffering check

/**
 * This class provides the initialisation and connection generation logic for wifi connections.
 */
class WiFiInitialisation : public DeviceInitialisation {
private:
	WiFiServer *server;
public:
    explicit WiFiInitialisation(WiFiServer* server) : server(server) {}

    bool attemptInitialisation() override;

    bool attemptNewConnection(BaseRemoteServerConnection *transport) override;
};

/**
 * This function converts from a RSSI (Radio Strength indicator)
 * measurement into a series of icons (of the ones we have defined
 * in the stock icons. The input is the RSSI figure in dB as an
 * integer.
 * @param strength the signal strength (usually negative) as an int
 * @return a state that can be used with the standard wifi TitleWidget
 */
int fromWiFiRSSITo4StateIndicator(int strength);

} // namespace tcremote

#ifndef TC_MANUAL_NAMESPACING
using namespace tcremote;
#endif // TC_MANUAL_NAMESPACING

#endif /* TCMENU_WIFITRANSPORT_H_ */
#endif
