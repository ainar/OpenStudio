/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CoilCoolingLowTempRadiantConstFlow.hpp"
#include "CoilCoolingLowTempRadiantConstFlow_Impl.hpp"
#include "ZoneHVACLowTempRadiantConstFlow.hpp"
#include "ZoneHVACLowTempRadiantConstFlow_Impl.hpp"
#include "ZoneHVACComponent.hpp"
#include "ZoneHVACComponent_Impl.hpp"
#include "Schedule.hpp"
#include "Schedule_Impl.hpp"
#include "ScheduleTypeLimits.hpp"
#include "ScheduleTypeRegistry.hpp"
#include "Model.hpp"
#include "Model_Impl.hpp"
#include "Node.hpp"
#include "Node_Impl.hpp"
#include "PlantLoop.hpp"
#include "PlantLoop_Impl.hpp"

#include <utilities/idd/IddFactory.hxx>

#include <utilities/idd/OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlow_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include "../utilities/core/Assert.hpp"
#include "../utilities/data/DataEnums.hpp"

namespace openstudio {
namespace model {

  namespace detail {

    CoilCoolingLowTempRadiantConstFlow_Impl::CoilCoolingLowTempRadiantConstFlow_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : StraightComponent_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == CoilCoolingLowTempRadiantConstFlow::iddObjectType());
    }

    CoilCoolingLowTempRadiantConstFlow_Impl::CoilCoolingLowTempRadiantConstFlow_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : StraightComponent_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == CoilCoolingLowTempRadiantConstFlow::iddObjectType());
    }

    CoilCoolingLowTempRadiantConstFlow_Impl::CoilCoolingLowTempRadiantConstFlow_Impl(const CoilCoolingLowTempRadiantConstFlow_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : StraightComponent_Impl(other, model, keepHandle) {}

    const std::vector<std::string>& CoilCoolingLowTempRadiantConstFlow_Impl::outputVariableNames() const {
      static const std::vector<std::string> result;
      return result;
    }

    IddObjectType CoilCoolingLowTempRadiantConstFlow_Impl::iddObjectType() const {
      return CoilCoolingLowTempRadiantConstFlow::iddObjectType();
    }

    unsigned CoilCoolingLowTempRadiantConstFlow_Impl::inletPort() const {
      return OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterInletNodeName;
    }

    unsigned CoilCoolingLowTempRadiantConstFlow_Impl::outletPort() const {
      return OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterOutletNodeName;
    }

    std::vector<ScheduleTypeKey> CoilCoolingLowTempRadiantConstFlow_Impl::getScheduleTypeKeys(const Schedule& schedule) const {
      std::vector<ScheduleTypeKey> result;
      UnsignedVector fieldIndices = getSourceIndices(schedule.handle());
      UnsignedVector::const_iterator b(fieldIndices.begin());
      UnsignedVector::const_iterator e(fieldIndices.end());
      if (std::find(b, e, OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingHighWaterTemperatureScheduleName) != e) {
        result.push_back(ScheduleTypeKey("CoilCoolingLowTempRadiantConstFlow", "Cooling High Water Temperature"));
      }
      if (std::find(b, e, OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingLowWaterTemperatureScheduleName) != e) {
        result.push_back(ScheduleTypeKey("CoilCoolingLowTempRadiantConstFlow", "Cooling Low Water Temperature"));
      }
      if (std::find(b, e, OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingHighControlTemperatureScheduleName) != e) {
        result.push_back(ScheduleTypeKey("CoilCoolingLowTempRadiantConstFlow", "Cooling High Control Temperature"));
      }
      if (std::find(b, e, OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingLowControlTemperatureScheduleName) != e) {
        result.push_back(ScheduleTypeKey("CoilCoolingLowTempRadiantConstFlow", "Cooling Low Control Temperature"));
      }
      return result;
    }

    boost::optional<ZoneHVACComponent> CoilCoolingLowTempRadiantConstFlow_Impl::containingZoneHVACComponent() const {

      std::vector<ZoneHVACLowTempRadiantConstFlow> zoneHVACLowTempRadiantConstFlows;

      zoneHVACLowTempRadiantConstFlows = this->model().getConcreteModelObjects<ZoneHVACLowTempRadiantConstFlow>();

      for (const auto& zoneHVACLowTempRadiantConstFlow : zoneHVACLowTempRadiantConstFlows) {
        if (boost::optional<HVACComponent> coil = zoneHVACLowTempRadiantConstFlow.coolingCoil()) {
          if (coil->handle() == this->handle()) {
            return zoneHVACLowTempRadiantConstFlow;
          }
        }
      }
      return boost::none;
    }

    boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow_Impl::coolingHighWaterTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingHighWaterTemperatureScheduleName);
    }

    boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow_Impl::coolingLowWaterTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingLowWaterTemperatureScheduleName);
    }

    boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow_Impl::coolingHighControlTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingHighControlTemperatureScheduleName);
    }

    boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow_Impl::coolingLowControlTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingLowControlTemperatureScheduleName);
    }

    std::string CoilCoolingLowTempRadiantConstFlow_Impl::condensationControlType() const {
      boost::optional<std::string> value = getString(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CondensationControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool CoilCoolingLowTempRadiantConstFlow_Impl::isCondensationControlTypeDefaulted() const {
      return isEmpty(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CondensationControlType);
    }

    double CoilCoolingLowTempRadiantConstFlow_Impl::condensationControlDewpointOffset() const {
      boost::optional<double> value = getDouble(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CondensationControlDewpointOffset, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool CoilCoolingLowTempRadiantConstFlow_Impl::isCondensationControlDewpointOffsetDefaulted() const {
      return isEmpty(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CondensationControlDewpointOffset);
    }

    bool CoilCoolingLowTempRadiantConstFlow_Impl::setCoolingHighWaterTemperatureSchedule(Schedule& schedule) {
      bool result = setSchedule(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingHighWaterTemperatureScheduleName,
                                "CoilCoolingLowTempRadiantConstFlow", "Cooling High Water Temperature", schedule);
      return result;
    }

    void CoilCoolingLowTempRadiantConstFlow_Impl::resetCoolingHighWaterTemperatureSchedule() {
      bool result = setString(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingHighWaterTemperatureScheduleName, "");
      OS_ASSERT(result);
    }

    bool CoilCoolingLowTempRadiantConstFlow_Impl::setCoolingLowWaterTemperatureSchedule(Schedule& schedule) {
      bool result = setSchedule(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingLowWaterTemperatureScheduleName,
                                "CoilCoolingLowTempRadiantConstFlow", "Cooling Low Water Temperature", schedule);
      return result;
    }

    void CoilCoolingLowTempRadiantConstFlow_Impl::resetCoolingLowWaterTemperatureSchedule() {
      bool result = setString(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingLowWaterTemperatureScheduleName, "");
      OS_ASSERT(result);
    }

    bool CoilCoolingLowTempRadiantConstFlow_Impl::setCoolingHighControlTemperatureSchedule(Schedule& schedule) {
      bool result = setSchedule(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingHighControlTemperatureScheduleName,
                                "CoilCoolingLowTempRadiantConstFlow", "Cooling High Control Temperature", schedule);
      return result;
    }

    void CoilCoolingLowTempRadiantConstFlow_Impl::resetCoolingHighControlTemperatureSchedule() {
      bool result = setString(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingHighControlTemperatureScheduleName, "");
      OS_ASSERT(result);
    }

    bool CoilCoolingLowTempRadiantConstFlow_Impl::setCoolingLowControlTemperatureSchedule(Schedule& schedule) {
      bool result = setSchedule(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingLowControlTemperatureScheduleName,
                                "CoilCoolingLowTempRadiantConstFlow", "Cooling Low Control Temperature", schedule);
      return result;
    }

    void CoilCoolingLowTempRadiantConstFlow_Impl::resetCoolingLowControlTemperatureSchedule() {
      bool result = setString(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingLowControlTemperatureScheduleName, "");
      OS_ASSERT(result);
    }

    bool CoilCoolingLowTempRadiantConstFlow_Impl::setCondensationControlType(const std::string& condensationControlType) {
      bool result = setString(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CondensationControlType, condensationControlType);
      return result;
    }

    void CoilCoolingLowTempRadiantConstFlow_Impl::resetCondensationControlType() {
      bool result = setString(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CondensationControlType, "");
      OS_ASSERT(result);
    }

    bool CoilCoolingLowTempRadiantConstFlow_Impl::setCondensationControlDewpointOffset(double condensationControlDewpointOffset) {
      bool result =
        setDouble(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CondensationControlDewpointOffset, condensationControlDewpointOffset);
      OS_ASSERT(result);
      return result;
    }

    void CoilCoolingLowTempRadiantConstFlow_Impl::resetCondensationControlDewpointOffset() {
      bool result = setString(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CondensationControlDewpointOffset, "");
      OS_ASSERT(result);
    }

    std::vector<std::string> CoilCoolingLowTempRadiantConstFlow_Impl::condensationControlTypeValues() const {
      return CoilCoolingLowTempRadiantConstFlow::condensationControlTypeValues();
    }

    boost::optional<ModelObject> CoilCoolingLowTempRadiantConstFlow_Impl::coolingHighWaterTemperatureScheduleAsModelObject() const {
      OptionalModelObject result;
      OptionalSchedule intermediate = coolingHighWaterTemperatureSchedule();
      if (intermediate) {
        result = *intermediate;
      }
      return result;
    }

    boost::optional<ModelObject> CoilCoolingLowTempRadiantConstFlow_Impl::coolingLowWaterTemperatureScheduleAsModelObject() const {
      OptionalModelObject result;
      OptionalSchedule intermediate = coolingLowWaterTemperatureSchedule();
      if (intermediate) {
        result = *intermediate;
      }
      return result;
    }

    boost::optional<ModelObject> CoilCoolingLowTempRadiantConstFlow_Impl::coolingHighControlTemperatureScheduleAsModelObject() const {
      OptionalModelObject result;
      OptionalSchedule intermediate = coolingHighControlTemperatureSchedule();
      if (intermediate) {
        result = *intermediate;
      }
      return result;
    }

    boost::optional<ModelObject> CoilCoolingLowTempRadiantConstFlow_Impl::coolingLowControlTemperatureScheduleAsModelObject() const {
      OptionalModelObject result;
      OptionalSchedule intermediate = coolingLowControlTemperatureSchedule();
      if (intermediate) {
        result = *intermediate;
      }
      return result;
    }

    bool
      CoilCoolingLowTempRadiantConstFlow_Impl::setCoolingHighWaterTemperatureScheduleAsModelObject(const boost::optional<ModelObject>& modelObject) {
      if (modelObject) {
        OptionalSchedule intermediate = modelObject->optionalCast<Schedule>();
        if (intermediate) {
          Schedule schedule(*intermediate);
          return setCoolingHighWaterTemperatureSchedule(schedule);
        } else {
          return false;
        }
      } else {
        resetCoolingHighWaterTemperatureSchedule();
      }
      return true;
    }

    bool
      CoilCoolingLowTempRadiantConstFlow_Impl::setCoolingLowWaterTemperatureScheduleAsModelObject(const boost::optional<ModelObject>& modelObject) {
      if (modelObject) {
        OptionalSchedule intermediate = modelObject->optionalCast<Schedule>();
        if (intermediate) {
          Schedule schedule(*intermediate);
          return setCoolingLowWaterTemperatureSchedule(schedule);
        } else {
          return false;
        }
      } else {
        resetCoolingLowWaterTemperatureSchedule();
      }
      return true;
    }

    bool CoilCoolingLowTempRadiantConstFlow_Impl::setCoolingHighControlTemperatureScheduleAsModelObject(
      const boost::optional<ModelObject>& modelObject) {
      if (modelObject) {
        OptionalSchedule intermediate = modelObject->optionalCast<Schedule>();
        if (intermediate) {
          Schedule schedule(*intermediate);
          return setCoolingHighControlTemperatureSchedule(schedule);
        } else {
          return false;
        }
      } else {
        resetCoolingHighControlTemperatureSchedule();
      }
      return true;
    }

    bool
      CoilCoolingLowTempRadiantConstFlow_Impl::setCoolingLowControlTemperatureScheduleAsModelObject(const boost::optional<ModelObject>& modelObject) {
      if (modelObject) {
        OptionalSchedule intermediate = modelObject->optionalCast<Schedule>();
        if (intermediate) {
          Schedule schedule(*intermediate);
          return setCoolingLowControlTemperatureSchedule(schedule);
        } else {
          return false;
        }
      } else {
        resetCoolingLowControlTemperatureSchedule();
      }
      return true;
    }

    bool CoilCoolingLowTempRadiantConstFlow_Impl::addToNode(Node& node) {
      if (boost::optional<PlantLoop> plant = node.plantLoop()) {
        if (plant->demandComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }

      return false;
    }

    ComponentType CoilCoolingLowTempRadiantConstFlow_Impl::componentType() const {
      return ComponentType::Cooling;
    }

    std::vector<FuelType> CoilCoolingLowTempRadiantConstFlow_Impl::coolingFuelTypes() const {
      if (auto p_ = plantLoop()) {
        return p_->coolingFuelTypes();
      }
      return {};
    }

    std::vector<FuelType> CoilCoolingLowTempRadiantConstFlow_Impl::heatingFuelTypes() const {
      return {};
    }

    std::vector<AppGFuelType> CoilCoolingLowTempRadiantConstFlow_Impl::appGHeatingFuelTypes() const {
      return {};
    }

  }  // namespace detail

  CoilCoolingLowTempRadiantConstFlow::CoilCoolingLowTempRadiantConstFlow(const Model& model, Schedule& coolingHighWaterTemperatureSchedule,
                                                                         Schedule& coolingLowWaterTemperatureSchedule,
                                                                         Schedule& coolingHighControlTemperatureSchedule,
                                                                         Schedule& coolingLowControlTemperatureSchedule)
    : StraightComponent(CoilCoolingLowTempRadiantConstFlow::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>());

    bool ok = setCoolingHighWaterTemperatureSchedule(coolingHighWaterTemperatureSchedule);
    OS_ASSERT(ok);

    ok = setCoolingLowWaterTemperatureSchedule(coolingLowWaterTemperatureSchedule);
    OS_ASSERT(ok);

    ok = setCoolingHighControlTemperatureSchedule(coolingHighControlTemperatureSchedule);
    OS_ASSERT(ok);

    ok = setCoolingLowControlTemperatureSchedule(coolingLowControlTemperatureSchedule);
    OS_ASSERT(ok);
  }

  IddObjectType CoilCoolingLowTempRadiantConstFlow::iddObjectType() {
    return {IddObjectType::OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlow};
  }

  std::vector<std::string> CoilCoolingLowTempRadiantConstFlow::condensationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CondensationControlType);
  }

  boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow::coolingHighWaterTemperatureSchedule() const {
    return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->coolingHighWaterTemperatureSchedule();
  }

  boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow::coolingLowWaterTemperatureSchedule() const {
    return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->coolingLowWaterTemperatureSchedule();
  }

  boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow::coolingHighControlTemperatureSchedule() const {
    return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->coolingHighControlTemperatureSchedule();
  }

  boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow::coolingLowControlTemperatureSchedule() const {
    return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->coolingLowControlTemperatureSchedule();
  }

  std::string CoilCoolingLowTempRadiantConstFlow::condensationControlType() const {
    return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->condensationControlType();
  }

  bool CoilCoolingLowTempRadiantConstFlow::isCondensationControlTypeDefaulted() const {
    return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->isCondensationControlTypeDefaulted();
  }

  double CoilCoolingLowTempRadiantConstFlow::condensationControlDewpointOffset() const {
    return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->condensationControlDewpointOffset();
  }

  bool CoilCoolingLowTempRadiantConstFlow::isCondensationControlDewpointOffsetDefaulted() const {
    return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->isCondensationControlDewpointOffsetDefaulted();
  }

  bool CoilCoolingLowTempRadiantConstFlow::setCoolingHighWaterTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->setCoolingHighWaterTemperatureSchedule(schedule);
  }

  void CoilCoolingLowTempRadiantConstFlow::resetCoolingHighWaterTemperatureSchedule() {
    getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->resetCoolingHighWaterTemperatureSchedule();
  }

  bool CoilCoolingLowTempRadiantConstFlow::setCoolingLowWaterTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->setCoolingLowWaterTemperatureSchedule(schedule);
  }

  void CoilCoolingLowTempRadiantConstFlow::resetCoolingLowWaterTemperatureSchedule() {
    getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->resetCoolingLowWaterTemperatureSchedule();
  }

  bool CoilCoolingLowTempRadiantConstFlow::setCoolingHighControlTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->setCoolingHighControlTemperatureSchedule(schedule);
  }

  void CoilCoolingLowTempRadiantConstFlow::resetCoolingHighControlTemperatureSchedule() {
    getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->resetCoolingHighControlTemperatureSchedule();
  }

  bool CoilCoolingLowTempRadiantConstFlow::setCoolingLowControlTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->setCoolingLowControlTemperatureSchedule(schedule);
  }

  void CoilCoolingLowTempRadiantConstFlow::resetCoolingLowControlTemperatureSchedule() {
    getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->resetCoolingLowControlTemperatureSchedule();
  }

  bool CoilCoolingLowTempRadiantConstFlow::setCondensationControlType(const std::string& condensationControlType) {
    return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->setCondensationControlType(condensationControlType);
  }

  void CoilCoolingLowTempRadiantConstFlow::resetCondensationControlType() {
    getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->resetCondensationControlType();
  }

  bool CoilCoolingLowTempRadiantConstFlow::setCondensationControlDewpointOffset(double condensationControlDewpointOffset) {
    return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->setCondensationControlDewpointOffset(condensationControlDewpointOffset);
  }

  void CoilCoolingLowTempRadiantConstFlow::resetCondensationControlDewpointOffset() {
    getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->resetCondensationControlDewpointOffset();
  }

  /// @cond
  CoilCoolingLowTempRadiantConstFlow::CoilCoolingLowTempRadiantConstFlow(std::shared_ptr<detail::CoilCoolingLowTempRadiantConstFlow_Impl> impl)
    : StraightComponent(std::move(impl)) {}
  /// @endcond

}  // namespace model
}  // namespace openstudio
