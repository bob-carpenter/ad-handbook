# ad-handbook

This is the source repository for the *Automatic Differentiation
Handbook*.  To build the HTML version of the book from R using the
`bookdown` package,

```
> library(bookdown)
> render_book('index.Rmd')
```

The first page of the book can then be found in the file
`_book/index.html`.

A web connection is required to render the mathematics in the web
version because it uses MathJax.
