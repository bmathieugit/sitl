#include <lib/vector.hpp>
#include <lib/string.hpp>

#include <lib/logger.hpp>
#include <source_location>

int main()
{

  lib::String key = "lkqjsdijazd";
  lib::String clear = "Ut tempor dolor nec libero laoreet imperdiet."
                      " Integer at tortor sapien. Etiam accumsan vel ipsum blandit pellentesque."
                      " Nullam elementum, dui ac fermentum bibendum, neque mauris dignissim sapien,"
                      " in ullamcorper dui orci ut arcu. Aenean vehicula consequat nisl, ut tristique"
                      " nisi congue sed. Praesent ante nulla, condimentum congue tempor vel, luctus in"
                      " dui. Proin at ipsum vulputate, faucibus urna sed, vulputate ex. Etiam tristique"
                      " orci vel dui aliquam tincidunt id ut risus. Morbi eget ipsum massa. Proin pretium"
                      " vestibulum metus vel molestie. Donec laoreet pretium augue, eget porta neque"
                      " eleifend eget. Proin sit amet ullamcorper nisl, quis congue turpis. Sed auctor"
                      " nisl nec sapien rhoncus, at blandit sapien scelerisque.";

  lib::String crypted = clear;

  lib::StringSpan cryptedspan = crypted;
  auto [frame, tail] = cryptedspan.split(key.size());

  while (!frame.empty())
  {
    for (lib::Size i = 0; i < frame.size(); ++i)
      frame[i] = key[i] + frame[i];

    auto [fr, tl] = tail.split(key.size());
    frame = fr;
    tail = tl;
  }

  lib::String uncrypted = crypted;

  lib::StringSpan uncryptedspan = uncrypted;
  auto [uframe, utail] = uncryptedspan.split(key.size());

  while (!uframe.empty())
  {
    for (lib::Size i = 0; i < uframe.size(); ++i)
      uframe[i] = uframe[i] - key[i];

    auto [fr, tl] = utail.split(key.size());
    uframe = fr;
    utail = tl;
  }

  lib::logger::info("clear '#'", clear);
  lib::logger::info("crypted '#'", crypted);
  lib::logger::info("uncrypted '#'", uncrypted);
}