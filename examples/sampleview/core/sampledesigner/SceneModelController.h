// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SCENEMODELCONTROLLER_H
#define SCENEMODELCONTROLLER_H

#include <functional>

namespace ModelView {
class SessionModel;
}

class DesignerScene;
class IView;
class NodeEditorConnection;
class QGraphicsItem;
template <class T> class QList;
class SampleModel;

//! Manages scene-model communication.
class SceneModelController
{
public:
    using ModelCommand = std::function<void (ModelView::SessionModel& model)>;

    explicit SceneModelController(DesignerScene& scene, SampleModel* model);
    ~SceneModelController();

    //! Propagates deletion of views on the scene to the model
    void onDelete(const QList<QGraphicsItem*>& views);
    //! Propagates view connection to the model
    void onConnect(NodeEditorConnection* connection);

    const SampleModel* model() const { return m_model; }

    //! Sets a command to model for later execution
    void setDelayedCommand(ModelCommand command);
    void executeDelayedCommand();

private:
    void onModelChange();
    void onModelDestroyed();

    DesignerScene& m_scene;
    SampleModel* m_model;
    bool m_block;
    ModelCommand m_command;
};

#endif // SCENEMODELCONTROLLER_H