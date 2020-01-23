// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialtablewidget.h"
#include "materialtableview.h"
#include <mvvm/viewmodel/abstractviewmodel.h>
#include <mvvm/viewmodel/standardviewmodels.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>
#include "materialmodel.h"
#include "materialselectionmodel.h"
#include <QVBoxLayout>

MaterialTableWidget::MaterialTableWidget(MaterialModel* material_model, QWidget* parent)
    : QWidget(parent), material_model(material_model),
      view_model(ModelView::Utils::CreatePropertyTableViewModel(material_model)),
      selection_model(new MaterialSelectionModel(view_model.get(), this)),
      table_view(new MaterialTableView), m_delegate(std::make_unique<ModelView::ViewModelDelegate>())
{
    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(table_view);
    setLayout(layout);

    table_view->setModel(view_model.get());
    table_view->setItemDelegate(m_delegate.get());
}

MaterialTableWidget::~MaterialTableWidget() = default;

MaterialSelectionModel* MaterialTableWidget::selectionModel() const
{
    return selection_model;
}
