/*
Copyright 2019 <Julian Komaromy>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "Keycoder.h"

namespace Keycoder
{
    std::array<Keycode, 256> keycodes;

    //copy the keycodes into the keycode array
    void generateKeycodes(const matrix_t& matrix) 
    {
        std::set<uint8_t> buffer;
        for (auto& l : matrix)
        {
            for (auto& r : l)
            {
                for (auto& vk : r)
                {
                    auto current = vk.getKeycodes();
                    buffer.insert(current.begin(), current.end());
                }
            }
        }
    }

    uint8_t encode(Keycode kc)
    {
        //find the index of the keycode inside the keycode array
        //also cast it to a byte, this always has to succeed
        //because the array is of size 2^8
        return static_cast<uint8_t>(std::distance(keycodes.begin(), 
                    std::find(keycodes.begin(), keycodes.end(), kc))); 
    }

    Keycode decode(uint8_t kc)
    {
        return keycodes[kc];
    }
}
