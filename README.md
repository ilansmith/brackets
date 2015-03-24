# brackets
Implementation of solution for Hola reported interview question.

url: https://www.dropbox.com/s/fyh7x4gls2drtwj/IMG_20141209_101953.jpg?dl=0

Hello

- Assume most recet language standard are available (ES5, SE8, C11, C++11...).
- We expect good performance.
- If missing m ore requirements details, just make reasonable asumptions
  of your own.
- Solution must be simple and compact.
  No defensive coding, no comments, no unrequested features.
  Only one file 1--20 lines of code
- Work only inside Google Docs: no external editor/IDE/debugger, no copy-paste
  to/from such an editor. We must see the flow of how you write the code.

Implement function check(text) wich checks whether brackets within text are
correctly nested. You need to consider brackets of three kinds: (), [], {}.

Examples:

check("a(b)") -> true
check("[{}]") -> true
check("[([") -> false
check("}{") -> false
check("z([{}-()]{a})") -> true
check("") -> true
