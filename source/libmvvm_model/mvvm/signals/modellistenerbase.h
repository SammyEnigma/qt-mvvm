// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SIGNALS_MODELLISTENERBASE_H
#define MVVM_SIGNALS_MODELLISTENERBASE_H

#include <mvvm/interfaces/modellistenerinterface.h>

namespace ModelView
{

class SessionModel;

//! Provides sets of methods to subscribe to various signals generated by SessionModel.
//! Automatically tracks the time of life of SessionModel. Unsubscribes from the model on
//! own destruction.

class MVVM_MODEL_EXPORT ModelListenerBase : public ModelListenerInterface
{
public:
    ModelListenerBase(SessionModel* model);
    ~ModelListenerBase() override;

    // 'client' is not used here, since 'this' is used

    void setOnDataChange(Callbacks::item_int_t f, Callbacks::slot_t client = {}) override;
    void setOnItemInserted(Callbacks::item_tagrow_t f, Callbacks::slot_t client = {}) override;
    void setOnItemRemoved(Callbacks::item_tagrow_t f, Callbacks::slot_t client = {}) override;
    void setOnAboutToRemoveItem(Callbacks::item_tagrow_t f, Callbacks::slot_t client = {}) override;
    void setOnModelDestroyed(Callbacks::model_t f, Callbacks::slot_t client = {}) override;
    void setOnModelAboutToBeReset(Callbacks::model_t f, Callbacks::slot_t client = {}) override;
    void setOnModelReset(Callbacks::model_t f, Callbacks::slot_t client = {}) override;

    void unsubscribe(Callbacks::slot_t client = {}) override;

protected:
    SessionModel* m_model{nullptr};
};

} // namespace ModelView

#endif // MVVM_SIGNALS_MODELLISTENERBASE_H
