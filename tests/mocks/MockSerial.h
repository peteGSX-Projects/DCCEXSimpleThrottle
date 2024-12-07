/*
 *  © 2024 Peter Cole
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this code.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MOCKSERIAL_H
#define MOCKSERIAL_H

#include <Stream.h>

/// @brief MockSerial class to ensure application can build with preprocessor macros
class MockSerial : public Stream {
public:
  /// @brief Implement Stream class methods
  virtual int available() override { return 0; }
  virtual int read() override { return -1; }
  virtual int peek() override { return -1; }

  // Print method implementations (inherited via Stream)
  virtual size_t write(uint8_t) override { return 1; }

  // Additional Stream/Print methods to satisfy the interface
  void begin(unsigned long) {} // For serial initialization
  void print(const char *) {}
  void println(const char *) {}
  void print(int) {}
  void println(int) {}
};

// Declare global mock objects that match your preprocessor macros
extern MockSerial Serial;
extern MockSerial Serial1;

#endif
