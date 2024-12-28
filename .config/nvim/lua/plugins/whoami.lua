-- Получаем имя пользователя из системы и добавляем его в vim.g.instant_username
vim.g.instant_username = os.getenv("USER") or os.getenv("USERNAME")

