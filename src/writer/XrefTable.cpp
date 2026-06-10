/**
 *
 *  @file XrefTable.cpp
 *  @author Gaspard Kirira
 *
 *  Copyright 2026, Gaspard Kirira.
 *  All rights reserved.
 *  https://github.com/rixcpp/pdf
 *
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  Rix
 *
 */

#include <rix/pdf/writer/XrefTable.hpp>

#include <iomanip>
#include <sstream>

namespace rixlib::pdf::writer
{
  XrefTable::XrefTable(const std::vector<std::size_t> &offsets)
      : offsets_(offsets)
  {
  }

  void XrefTable::write(
      std::string &output,
      int root_object_id,
      int info_object_id) const
  {
    const std::size_t xref_offset = output.size();
    const auto object_count = offsets_.size();

    output += "xref\n";
    output += "0 ";
    output += std::to_string(object_count);
    output += "\n";

    output += "0000000000 65535 f \n";

    for (std::size_t object_id = 1; object_id < object_count; ++object_id)
    {
      std::ostringstream line;
      line << std::setw(10)
           << std::setfill('0')
           << offsets_[object_id]
           << " 00000 n \n";

      output += line.str();
    }

    output += "trailer\n";
    output += "<< /Size ";
    output += std::to_string(object_count);
    output += " /Root ";
    output += std::to_string(root_object_id);
    output += " 0 R";

    if (info_object_id > 0)
    {
      output += " /Info ";
      output += std::to_string(info_object_id);
      output += " 0 R";
    }

    output += " >>\n";
    output += "startxref\n";
    output += std::to_string(xref_offset);
    output += "\n";
    output += "%%EOF\n";
  }
} // namespace rixlib::pdf::writer
