// Copyright (c) the JPEG XL Project Authors. All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "lib/jxl/enc_photon_noise.h"

#include "lib/jxl/noise.h"
#include "lib/jxl/testing.h"

namespace jxl {
namespace {

TEST(EncPhotonNoiseTest, LUTs) {
  const double kTolerance = 1e-6;
  EXPECT_ARRAY_NEAR(
      SimulatePhotonNoise(/*xsize=*/6000, /*ysize=*/4000, /*iso=*/100).lut,
      (NoiseParams::Lut{0.00259652, 0.0139648, 0.00681551, 0.00632582,
                        0.00694917, 0.00803922, 0.00934574, 0.0107607}),
      kTolerance);
  EXPECT_ARRAY_NEAR(
      SimulatePhotonNoise(/*xsize=*/6000, /*ysize=*/4000, /*iso=*/800).lut,
      (NoiseParams::Lut{0.02077220, 0.0420923, 0.01820690, 0.01439020,
                        0.01293670, 0.01254030, 0.01277390, 0.0134161}),
      kTolerance);
  EXPECT_ARRAY_NEAR(
      SimulatePhotonNoise(/*xsize=*/6000, /*ysize=*/4000, /*iso=*/6400).lut,
      (NoiseParams::Lut{0.1661770, 0.1691120, 0.05309080, 0.03963960,
                        0.03357410, 0.03001650, 0.02776740, 0.0263478}),
      kTolerance);

  // Lower when measured on a per-pixel basis as there are fewer of them.
  EXPECT_ARRAY_NEAR(
      SimulatePhotonNoise(/*xsize=*/4000, /*ysize=*/3000, /*iso=*/6400).lut,
      (NoiseParams::Lut{0.0830886, 0.1008720, 0.0367748, 0.0280305, 0.0240236,
                        0.0218040, 0.0205771, 0.0200058}),
      kTolerance);
}

}  // namespace
}  // namespace jxl
