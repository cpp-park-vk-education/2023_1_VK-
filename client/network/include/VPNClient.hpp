#pragma once

#include "VPNContext.hpp"

class VPN {
public:
	virtual bool runVPN() = 0;
	virtual bool stopVPN() = 0;
};

class VPNClient: VPN {
public:
	void setVPNContext(VpnContext);
	bool runVPN() override;
	bool stopVPN() override;
private:
	User vpn_user;
	VpnContext vpn_context;
	Config config_cli;
};
