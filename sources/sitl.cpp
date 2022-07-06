#include <lib/string.hpp>
#include <lib/logger.hpp>
#include <lib/args.hpp>
#include <lib/vector.hpp>

#include <sitl.hpp>

/**
 * Sitl va lire la source ligne par ligne
 * Chaque ligne va être identifiée pour
 * permetttre de mettre en place l'interprétation
 * du langage ligne par ligne.
 * On validera que la ligne veut dire quelque
 * puis on opéra l'action qu'elle est censée
 * lancer. Pour cela on lit la ligne, on la
 * place dans une string. On regarde le premier
 * token de la ligne (après avoir ignorer les
 * espaces). Ce premier token orientera l'intépretation
 * de la ligne vers le bon agent. Chaque agent de
 * compilation est ensuite responsable de traiter
 * la ligne comme il l'entend. On peut donc créer
 * un Trait/Concept Agent qui conceptualise ce que
 * doit faire un agent implémenter. Un agent doit
 * pouvoir tester si un string correspond à son
 * pattern de ligne à prendre compte. Nous aurons
 * donc une fonction bool test(String) à implementer.
 * De plus, l'agent doit aussi pouvoir faire quelque
 * chose de cette ligne si le "test" est true.
 * Nous aurons donc une fonction void act(String) qui
 * effectuera l'action implementée pour l'agent.
 */

#include <lib/tuple.hpp>

int main(int argc, char **argv)
{
  namespace logger = sitl::logger;
  sitl::CommandLine args(argc, argv);

  if (args.contains(sitl::sr("file")))
  {
    sitl::StringCRange fname = args.value(sitl::sr("file"));
    logger::debug("file name found, fname");
  }

  auto proclines = sitl::ProceduralLineyser()(
      sitl::ProceduralGTokenizer()(
          sitl::sr(
              "struct string\n"
              "begin\n"
              "  param char b\n"
              "  param char e\n"
              "end\n"
              "let int i '(+ i (- 1 12))'")));
  for (const sitl::Line &l : proclines)
    logger::debug("type ", (int)l.type, " depth ", l.depth);

  int i = 12;
  sitl::Tuple<int &, int> t(i, 24);
  t.get<0>() = 14;
  logger::debug("value 1 : ", t.get<0>(),
                "; value 2 : ", t.get<1>(),
                ";value orig : ", i);

  sitl::Tuple<int &, int> t2 = t;
  logger::debug("value 1 : ", t2.get<0>(),
                "; value 2 : ", t2.get<1>(),
                ";value orig : ", i);
  t.get<0>() = 15;

  logger::debug("value 1 : ", t2.get<0>(),
                "; value 2 : ", t2.get<1>(),
                ";value orig : ", i);

  logger::debug("value 1 : ", t.get<0>(),
                "; value 2 : ", t.get<1>(),
                ";value orig : ", i);

  return 0;
}
