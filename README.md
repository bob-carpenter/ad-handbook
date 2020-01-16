# ad-handbook

This is the source repository for the *Automatic Differentiation
Handbook*.

## Contributing

Please create pull requests or simply leave an issue.  All
contributions will be credited in the book itself.

## Licensing

The code is licensed under BSD-3 and the text under CC-BY-ND-NC 4.0.
All contributions are made in accorance with this license under the
terms of use for GitHub.

## Building the book

#### Prerequisites

The following R packages must be installed in order to build the book:

```
tufte
reshape
```

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
