// Copyright (c) the JPEG XL Project Authors. All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <jxl/memory_manager.h>

#include <utility>

#include "lib/jxl/dec_bit_reader.h"
#include "lib/jxl/enc_aux_out.h"
#include "lib/jxl/enc_bit_writer.h"
#include "lib/jxl/image_metadata.h"
#include "lib/jxl/test_memory_manager.h"
#include "lib/jxl/test_utils.h"
#include "lib/jxl/testing.h"

namespace jxl {
namespace {

TEST(ImageBundleTest, ExtraChannelName) {
  JxlMemoryManager* memory_manager = jxl::test::MemoryManager();
  AuxOut aux_out;
  BitWriter writer{memory_manager};
  BitWriter::Allotment allotment(&writer, 99);

  ImageMetadata metadata;
  ExtraChannelInfo eci;
  eci.type = ExtraChannel::kBlack;
  eci.name = "testK";
  metadata.extra_channel_info.push_back(std::move(eci));
  ASSERT_TRUE(WriteImageMetadata(metadata, &writer, /*layer=*/0, &aux_out));
  writer.ZeroPadToByte();
  allotment.ReclaimAndCharge(&writer, /*layer=*/0, &aux_out);

  BitReader reader(writer.GetSpan());
  ImageMetadata metadata_out;
  ASSERT_TRUE(ReadImageMetadata(&reader, &metadata_out));
  EXPECT_TRUE(reader.Close());
  EXPECT_EQ("testK", metadata_out.Find(ExtraChannel::kBlack)->name);
}

}  // namespace
}  // namespace jxl
