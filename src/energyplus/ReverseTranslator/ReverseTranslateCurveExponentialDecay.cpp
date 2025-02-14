/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ReverseTranslator.hpp"

#include "../../model/CurveExponentialDecay.hpp"
#include "../../model/CurveExponentialDecay_Impl.hpp"

#include <utilities/idd/Curve_ExponentialDecay_FieldEnums.hxx>

using namespace openstudio::model;

namespace openstudio {
namespace energyplus {

  boost::optional<ModelObject> ReverseTranslator::translateCurveExponentialDecay(const WorkspaceObject& workspaceObject) {
    CurveExponentialDecay curve(m_model);

    OptionalString s;
    OptionalDouble d;

    if ((s = workspaceObject.name())) {
      curve.setName(*s);
    }

    if ((d = workspaceObject.getDouble(Curve_ExponentialDecayFields::Coefficient1C1))) {
      curve.setCoefficient1C1(*d);
    }
    if ((d = workspaceObject.getDouble(Curve_ExponentialDecayFields::Coefficient2C2))) {
      curve.setCoefficient2C2(*d);
    }
    if ((d = workspaceObject.getDouble(Curve_ExponentialDecayFields::Coefficient3C3))) {
      curve.setCoefficient3C3(*d);
    }
    if ((d = workspaceObject.getDouble(Curve_ExponentialDecayFields::MinimumValueofx))) {
      curve.setMinimumValueofx(*d);
    }
    if ((d = workspaceObject.getDouble(Curve_ExponentialDecayFields::MaximumValueofx))) {
      curve.setMaximumValueofx(*d);
    }
    if ((d = workspaceObject.getDouble(Curve_ExponentialDecayFields::MinimumCurveOutput))) {
      curve.setMinimumCurveOutput(*d);
    }
    if ((d = workspaceObject.getDouble(Curve_ExponentialDecayFields::MaximumCurveOutput))) {
      curve.setMaximumCurveOutput(*d);
    }
    if ((s = workspaceObject.getString(Curve_ExponentialDecayFields::InputUnitTypeforx, false, true))) {
      curve.setInputUnitTypeforx(*s);
    }
    if ((s = workspaceObject.getString(Curve_ExponentialDecayFields::OutputUnitType, false, true))) {
      curve.setOutputUnitType(*s);
    }

    return curve;
  }

}  // namespace energyplus
}  // namespace openstudio
