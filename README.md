# sitl
Simple Information Technology Language

Mots clés du langage
```c
type del copy build move alias self
const default while for if else elif 
return break continue local literal 
```

Types de bases 
```c
i8, i16, i32, i64, u8, u16, u32, u64
```

Alias de types de bases 
```c
alias char u8
alias wchar u32
alias string char[] 
alias wstring wchar[]
```

Types utilisateur
```c
type person
{
  string name 
  string firstname
  u8 age
}

build person
(
  string name
  string firstname
  u8 age
)
{
  self.name = name
  self.firstname = firstname
  self.age = age
}

copy person
(
  const person p
)
{
  self.name = p.name
  self.firstname = p.name
  self.age = p.age
}

move person
(
  person p
)
{
  self.name := p.name
  self.firstname := p.firstname
  self.age := p.age
}

del person
()
{
  del self.name
  del self.firstname
  del self.age
}
```

On peut aussi le faire par défaut :
```c
type person 
{
  string name
  string firstname
  int age
}

build person
(
  string name
  string firstname
  int age
)
{
  self.name = name
  self.firstname = firstname
  self.age = age
}

default copy person
default move person
default del person 
```

ou même plus simplement :
```c
type person
{
  string name
  string firstname
  int age
}

default build person
default move person
default copy person
default del person

```

ou le plus simplement : 

```c
type person
{
  string name
  string firstname
  int age
}
```

Déclaration d'une fonction:
```c
local i8 SUCCES = 0
local i8 FAILURE = 1

i32 main
(
  i32 argc
  string[] args 
)
{
  printf "%s" "hello world!"
  return SUCCESS
}
```

Déclaration d'une variable:
```c
int age = 12
int age2 = age + 12
```

Arithémtique :
```c

```
