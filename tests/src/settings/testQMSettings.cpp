/*****************************************************************************
<GPL_HEADER>

    PIMD-QMCF
    Copyright (C) 2023-now  Jakob Gamper

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

<GPL_HEADER>
******************************************************************************/

#include "qmSettings.hpp"   // for QMSettings, QMMethod

#include "gtest/gtest.h"   // for Message, TestPartResult
#include <gtest/gtest.h>   // for Test, InitGoogleTest, RUN_ALL_TESTS, EXPECT_EQ
#include <memory>          // for allocator

TEST(QMSettingsTest, SetQMMethodTest)
{
    settings::QMSettings::setQMMethod("dftbplus");
    EXPECT_EQ(settings::QMSettings::getQMMethod(), settings::QMMethod::DFTBPLUS);

    settings::QMSettings::setQMMethod("none");
    EXPECT_EQ(settings::QMSettings::getQMMethod(), settings::QMMethod::NONE);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return ::RUN_ALL_TESTS();
}