//
// Created by xizor on 20/05/18.
//

#ifndef EMULATIONSTATION_ALL_GUINETPLAY_H
#define EMULATIONSTATION_ALL_GUINETPLAY_H

#include <components/ComponentList.h>
#include "GuiComponent.h"
#include "components/NinePatchComponent.h"
#include "components/ComponentGrid.h"
#include "resources/Font.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <recalbox/RecalboxSystem.h>
#include <boost/thread.hpp>
#include <MenuThemeData.h>
#include "FileData.h"

namespace json = boost::property_tree;

class TextComponent;
class ButtonComponent;

#define TITLE_VERT_PADDING (Renderer::getScreenHeight()*0.0637f)

class GuiNetPlay : public GuiComponent
{
public:
	GuiNetPlay(Window* window);

	inline ~GuiNetPlay() { if (mList) mList->clear(); }

	inline void addRow(const ComponentListRow& row, bool setCursorHere = false, bool updateGeometry = true) { mList->addRow(row, setCursorHere, updateGeometry); if (updateGeometry) updateSize(); }

	void checkLobby();

	bool parseLobby();

	void populateGrid();

	void populateGridMeta(int i);

	void launch();

	FileData* findGame(std::string game);

	FileData* findRecursive(const std::vector<FileData*>& gameFolder, const std::string& gameName, const std::string& relativePath = "");

    std::pair<std::string, std::string> getCoreInfo(const std::string &name);

    void pingLobby();

	std::string pingHost(const std::string& ip);

	float getButtonGridHeight() const;

	void updateSize();

	bool input(InputConfig* config, Input input) override;

	std::vector<HelpPrompt> getHelpPrompts() override;

	void onSizeChanged() override;

	void update(int deltaTime) override;

	void render(const Eigen::Affine3f &parentTrans) override;

private:

	NinePatchComponent mBackground;
	BusyComponent mBusyAnim;
	ComponentGrid mGrid;
	std::shared_ptr<MenuTheme> mMenuTheme;

	std::shared_ptr<ComponentGrid> mGridMeta;
	std::shared_ptr<ComponentGrid> mGridMetaRight;
	std::shared_ptr<ComponentGrid> mButtonGrid;
	std::vector< std::shared_ptr<ButtonComponent> > mButtons;
	std::shared_ptr<TextComponent> mTitle;
	std::shared_ptr<ComponentList> mList;
	std::shared_ptr<TextComponent> mMetaText;
	std::shared_ptr<TextComponent> mLaunchText;

	std::vector<FileData*> mGames;
	std::vector<json::ptree::value_type> mRooms;
	std::vector<std::string> mPings;

	boost::thread *mHandle;

	bool mLoading;
	bool mLoaded = false;
	bool mLobbyLoaded;
	bool mLobbyChecked;

};

#endif //EMULATIONSTATION_ALL_GUINETPLAY_H
