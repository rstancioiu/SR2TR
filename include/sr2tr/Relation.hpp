#pragma once

#include <vector>

namespace sr2tr {

using Interval = std::pair<double, double>;
using Relation = std::vector<std::vector<Interval>>;

}  // namespace sr2tr