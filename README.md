# ad-handbook

This is the source repository for the *Automatic Differentiation
Handbook*.

## Pre-built pdf

Here's a pre-built pdf of a recent (but perhaps not the latest) **DRAFT**:

* [ad-handbook-draft.pdf](./ad-handbook-draft.pdf).

I don't have a pre-built version of the HTML yet, but I'll try to
figure out how to push that to my GitHub pages repo automatically one
of these days.


## Contributing

Please create

* issues for feature requests or reporting bugs/typos/brainos
* pull requests for contributions

If you contribute and want to be listed by name rather than GitHub
handle, please include that in the PR.  Also, if you'd rather not
be listed, say that, too!

## The C++ reference implementation

* C++ reference code directory: [`cpp/`](./cpp)

* Example directory:  [`cpp/examples/`](./cpp/examples)


## Licensing

The code is licensed under BSD-3 and the text under CC-BY-ND-NC 4.0.
All contributions are made in accorance with this license under the
terms of use for GitHub.


## Building the book

#### Prerequisites

The following system package must be installed:

* pandoc
* pandoc-citeproc

See the [instructions for installing pandoc](https://pandoc.org/installing.html).

The following R packages must be installed in order to build the book:

* bookdown
* tufte
* reshape
* ggplot2
* gridExtra
* formatR

They can be installed using, e.g.,

```
> install.pacakges('tufte')
```

#### Build steps

To build the HTML version of the book from R using the
`bookdown` package,

```
> library(bookdown)
> render_book('index.Rmd')
```

The first page of the book can then be found in the file
`_book/index.html`.

A web connection is required to render the mathematics in the web
version because it uses MathJax.

To build the PDF version of the book using a shell script,

```
> ./build-pdf.sh
```

and to build the HTML version,

```
> ./build-html.sh
```
