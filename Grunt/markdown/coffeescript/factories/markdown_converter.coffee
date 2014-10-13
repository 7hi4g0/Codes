# The factory
@MarkdownEditor.factory "MarkdownConverter", ->
  convert: (input) ->
    markdown.toHTML input
