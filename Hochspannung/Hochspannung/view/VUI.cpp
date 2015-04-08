#include "VUI.h"
#include "VMaster.h"
#include "../logic/LUtility.h"
#include "VPlayingField.h"
#include "VCoalPowerPlant.h"

NAMESPACE_VIEW_B


VUI::VUI(VMaster* vMaster, LUI* lUi)
	: vMaster(vMaster), IVUI(lUi)
{
	vMaster->setVUI(this);
	vMaster->registerObserver(this);
}

void VUI::initUI()
{
	vMaster->m_zf.AddDeviceKeyboard(&m_zkKeyboard);
	vMaster->m_zf.AddDeviceCursor(&m_zkCursor);
	vMaster->m_zf.AddDeviceMouse(&m_zkMouse);
}

void VUI::handleInput(float fTimeDelta)
{
	m_zkKeyboard.PlaceWASD(vMaster->m_zpCamera, fTimeDelta);
	m_zkKeyboard.SetWASDTranslationSensitivity(100.0);
	m_zkKeyboard.SetWASDRotationSensitivity(2.0);
    m_zkKeyboard.SetWASDLevelMin(100.0);
	m_zkKeyboard.SetWASDLevelMax(200.0);




	/* Picking */
	static bool pickingActive = false;

	if (m_zkCursor.ButtonPressedLeft()) {
		if (!pickingActive) {
			float f;

			CPlacement *pickedPlacement = m_zkCursor.PickPlacement();
			if (pickedPlacement == nullptr) {
				return;
			}

			std::vector<std::string> koord = split(pickedPlacement->GetName(), ';');

			if (koord.size() > 0) {
				DEBUG_OUTPUT("picked object = " << pickedPlacement->GetName());

				if (koord[0] == getClassName(VPlayingField)) {
					ASSERT(koord.size() == 3, "Not enough arguments in the placement name");

					int x = std::stoi(koord[1]);
					int y = std::stoi(koord[2]);

					dynamic_cast<VPlayingField*>(vMaster->views[getClassName(VPlayingField)])->tryBuildOnField<LCoalPowerPlant>(x, y);
				}

			}

			pickingActive = true;
		}
	}
	else if (m_zkCursor.ButtonPressedRight()) {
		if (!pickingActive) {
			float f;

			CPlacement *pickedPlacement = m_zkCursor.PickPlacement();
			if (pickedPlacement == nullptr) {
				return;
			}

			std::vector<std::string> koord = split(pickedPlacement->GetName(), ';');

			if (koord.size() > 0) {
				DEBUG_OUTPUT("picked object = " << pickedPlacement->GetName());

				if (koord[0] == getClassName(VPlayingField)) {
					ASSERT(koord.size() == 3, "Not enough arguments in the placement name");

					dynamic_cast<VPlayingField*>(vMaster->views[getClassName(VPlayingField)])->tryBuildOnField<LHydroelectricPowerPlant>(std::stoi(koord[1]), std::stoi(koord[2]));
				}
				else if (koord[0] == getClassName(VCoalPowerPlant)) {
					vMaster->getPlayingField()->tryRemoveObject(std::stoi(koord[1]), std::stoi(koord[2]));
				}

			}

			pickingActive = true;
		}
	}
	else {
		pickingActive = false;
	}
}


NAMESPACE_VIEW_E
