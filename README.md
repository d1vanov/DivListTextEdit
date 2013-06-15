DivListTextEdit
===============

Demo of solution of a problem with ordered lists in QTextEdit: when you delete one item in the middle, the list won't split itself into two. This demo shows how to achieve this behaviour. 

The problem is described in details in my post on [qt-project.org](http://qt-project.org/forums/viewthread/28669/) but I'll repeat it here for convenience. 

Description
===========

consider the following list:

1. item 1
2. item 2
3. item 3
4. item 4
  1. subitem 1
  2. subitem 2
5. item 5
6. item 6

Let’s say you want to delete the item 3. So you move the cursor there, press backspace a couple of times until “item 3” text is deleted and when you finally press backspace on empty line corresponding to element 3, by default QTextEdit provides the following resulting list:

1. item 1
2. item 2

3. item 4
  1. subitem 1
  2. subitem 2
4. item 5
5. item 6

I’d like to get another result, in particular I’d like to get two lists divided by the empty line remaining from the deleted item. Like this:

1. item 1
2. item 2

(empty line)

1. item 4
  1. subitem 1
  2. subitem 2
2. item 5
3. item 6

I haven’t found notices on this problem in the Internet, it looks like most or even all developers working with Qt and creating rich text editors accept the default way of forming the resulting list provided by QTextEdit in this case. That default behaviour can be observed in LibreOffice (not sure it uses QTextEdit but anyway), Calligra Word and other free office suites. I seem to have found a solution capable of overriding the default workflow with ordered lists of QTextEdit which the code demonstrates. 

License
=======

[Public domain](http://en.wikipedia.org/wiki/Public_domain)
