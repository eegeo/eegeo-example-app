// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "Menu.h"
#include "IMenuSectionViewModel.h"
#include "Types.h"

namespace ExampleApp
{
namespace Menu
{
class MenuSectionViewModel : public IMenuSectionViewModel, private Eegeo::NonCopyable
{
public:

	MenuSectionViewModel(const std::string& name, const std::string& icon, IMenuModel& menuModel, bool isExpandable);

	const std::string& Name() const
	{
		return m_name;
	};

	const std::string& Icon() const
	{
		return m_icon;
	};

	std::string Details() const
	{
		return "";
	};

	std::string SerializeJson() const;

	size_t Size() const;

	size_t GetTotalItemCount() const;

	MenuItemModel GetItemAtIndex(int index) const;

	bool IsExpanded() const
	{
		return m_isExpandable ? m_expanded : true;
	};
	bool IsExpandable() const
	{
		return m_isExpandable;
	}

	void Expand();
	void Contract();

private:

	std::string m_name;
	std::string m_icon;
	IMenuModel& m_menuModel;

	const bool m_isExpandable;
	bool m_expanded;
};
}
}
