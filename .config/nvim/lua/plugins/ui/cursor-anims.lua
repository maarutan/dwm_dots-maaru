require("smear_cursor").setup({
	smear_between_buffers = true, -- Размазывание при переключении между буферами
	smear_between_neighbor_lines = true, -- Размазывание при перемещении между соседними строками
	scroll_buffer_space = true, -- Размазывание в пространстве буфера при прокрутке
	legacy_computing_symbols_support = false, -- Поддержка символов старых вычислительных систем
})
