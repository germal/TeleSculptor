/*ckwg +29
 * Copyright 2018-2019 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither the name Kitware, Inc. nor the names of any contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TELESCULPTOR_VTKMAPTKPOINTHANDLEREPRESENTATION3D_H_
#define TELESCULPTOR_VTKMAPTKPOINTHANDLEREPRESENTATION3D_H_

// Telesculptor includes
#include "vtkMaptkAxesActor.h"

// VTK includes
#include <vtkPointHandleRepresentation3D.h>

// Forward declarations
class vtkRenderer;

class vtkMaptkPointHandleRepresentation3D
  : public vtkPointHandleRepresentation3D
{
public:
  vtkTypeMacro(vtkMaptkPointHandleRepresentation3D,
               vtkPointHandleRepresentation3D);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  static vtkMaptkPointHandleRepresentation3D* New();

  /**
   * Override widget interaction for custom constraints
   */
  void WidgetInteraction(double eventPos[2]) override;

  /**
   * Override build representation to show custom constraint axes
   */
  void BuildRepresentation() override;

  //@{
  /**
   * Set/Get whether to use a custom constraint.
   * In this mode, the constraint is exercised either along the Z axis or along
   * the XY plane. Defaults to false.
   */
  vtkSetMacro(CustomConstraint, int);
  vtkGetMacro(CustomConstraint, int);
  vtkBooleanMacro(CustomConstraint, int);
  //@}

  //@{
  /**
   * Override shallow and deep copy to add custom constraint.
   */
  void ShallowCopy(vtkProp* p) override;
  void DeepCopy(vtkProp* p) override;
  //@}

  //@{
  /**
   * Set/Get the axis to be constrained.
   */
  vtkSetMacro(ConstraintAxis, int);
  vtkGetMacro(ConstraintAxis, int);
  //@}

protected:
  vtkMaptkPointHandleRepresentation3D() = default;
  ~vtkMaptkPointHandleRepresentation3D() = default;

  // Override to ensure that the pick tolerance is always about the same as
  // handle size.
  int ComputeInteractionState(int X, int Y, int modify) override;

  // Constrained move focus
  void MoveFocusConstrained(double* p1, double* p2);

  // Constrained translate
  void TranslateConstrained(double* p1, double* p2, double* displaypos);

  /**
   * Update the axes
   */
  void UpdateAxes();

  // Member variables
  int CustomConstraint = 0;
  vtkNew<vtkMaptkAxesActor> AxesActor;

private:
  vtkMaptkPointHandleRepresentation3D(
    const vtkMaptkPointHandleRepresentation3D&) = delete;
  void operator=(const vtkMaptkPointHandleRepresentation3D) = delete;
};

#endif
