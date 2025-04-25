// kinematic_link_plugin.cc

#include <gz/sim/System.hh>
#include <gz/sim/Model.hh>
#include <gz/sim/Util.hh>
#include <gz/plugin/Register.hh>
#include <gz/math/Pose3.hh>
#include <gz/math/Vector3.hh>
#include "gz/sim/Link.hh"

using namespace gz;
using namespace sim;
using namespace systems;

class KinematicLinkPlugin
  : public System,
    public ISystemConfigure,
    public ISystemPreUpdate
{
  // Called once at startup; _entity is the Model this plugin is attached to
  void Configure(const Entity &_entity,
                 const std::shared_ptr<const sdf::Element> &_sdf,
                 EntityComponentManager &_ecm,
                 EventManager &/*_evtMgr*/) override
  {
    // Read link name from SDF
    this->linkName = _sdf->Get<std::string>("linkName");

    // Wrap model entity for convenience
    this->model = Model(_entity);

    // Find the link entity
    this->linkEntity = model.LinkByName(_ecm, this->linkName);

    // Cache its initial world pose
    this->initialPose = worldPose(this->linkEntity, _ecm);
  }

  // Called every simulation iteration, *before* physics update
  void PreUpdate(const UpdateInfo &/*_info*/,
                 EntityComponentManager &_ecm) override
  {
    // Snap the link back to its original pose
    this->model.SetWorldPoseCmd(_ecm, this->initialPose);

    // Zero out any linear & angular velocity
    Link link(this->linkEntity);
    link.SetLinearVelocity(_ecm, math::Vector3d::Zero);
    link.SetAngularVelocity(_ecm, math::Vector3d::Zero);
  }

private:
  std::string        linkName;
  Entity             linkEntity;
  math::Pose3d       initialPose;
  Model              model;
};

// Register as a Gazebo‐Harmonic system plugin
GZ_ADD_PLUGIN(KinematicLinkPlugin,
              System,
              KinematicLinkPlugin::ISystemConfigure,
              KinematicLinkPlugin::ISystemPreUpdate)

// Provide an unversioned alias so SDF `<plugin filename>` can just say "KinematicLinkPlugin"
GZ_ADD_PLUGIN_ALIAS(KinematicLinkPlugin, "gz::sim::systems::KinematicLinkPlugin")
