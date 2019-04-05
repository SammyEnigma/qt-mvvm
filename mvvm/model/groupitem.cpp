// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "groupitem.h"
#include "comboproperty.h"
#include "containerutils.h"
#include "taginfo.h"

namespace  {
std::string tag_name = "group_items";
}

using namespace ModelView;

GroupItem::~GroupItem() = default;

GroupItem::GroupItem(model_type modelType) :SessionItem(modelType),
    m_catalogue(std::make_unique<ItemCatalogue>()), m_current_index(0)
{
    registerTag(TagInfo::universalTag(tag_name), /*set_as_default*/true);
}

int GroupItem::currentIndex() const
{
    return m_current_index;
}

//! Returns currently selected item.

SessionItem* GroupItem::currentItem()
{
    return getItem("", m_current_index);
}

std::string GroupItem::currentType() const
{
    auto model_types = m_catalogue->modelTypes();
    return model_types[static_cast<size_t>(m_current_index)];
}

//! Sets item corresponding to given model type.

void GroupItem::setCurrentType(const std::string& model_type)
{
    auto model_types = m_catalogue->modelTypes();
    int index = Utils::IndexOfItem(model_types, model_type);
    if (index == -1)
        throw std::runtime_error("GroupItem::setCurrentType() -> Model type '"+model_type+
                                 "' doesn't belong to the group");

    m_current_index = index;
    update_combo();
}

//! Inits group item.

void GroupItem::init_group()
{
    update_combo();
    for (auto x : m_catalogue->modelTypes())
        insertItem(m_catalogue->create(x).release(), "", -1);
}

//! Creates ComboProperty representing the group and sets it as data role.

void GroupItem::update_combo()
{
    ComboProperty combo;
    combo.setValues(m_catalogue->labels());
    combo.setCurrentIndex(m_current_index);
    setDataIntern(combo.variant(), ItemDataRole::DATA);
}
