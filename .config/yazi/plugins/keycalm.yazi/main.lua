--- @sync entry
local M = {}

-- Function to set user configurations
M.setup = function(_, opts)
	opts = opts or {}

	-- Default configuration
	M.config = {
		limit = opts.limit or 10, -- Number of presses before blocking
		delay = opts.delay or 3, -- Block duration in seconds (also notification duration)
		notify_title = opts.notify_title or "Hold it, {user}!",
		notify_message = opts.notify_message or "🤠 Take it easy, cowboy!",
		notify_unblock = opts.notify_unblock or "      {key} 🥳",
	}
end

M.entry = function(state, job)
	local key = job.args[1]
	if not key then
		return
	end

	local config = M.config

	-- Initialize state variables
	state.keycalm_counts = state.keycalm_counts or {}
	state.keycalm_blocked = state.keycalm_blocked or {}
	state.keycalm_last_pressed = state.keycalm_last_pressed or {}

	-- Reset all counters and blocks on ESC
	if key == "<Esc>" then
		for k, _ in pairs(state.keycalm_counts) do
			state.keycalm_counts[k] = 0
			state.keycalm_blocked[k] = false
			state.keycalm_last_pressed[k] = 0
		end
		return
	end

	-- If key is blocked, check the delay timer
	if state.keycalm_blocked[key] then
		local elapsed_time = ya.time() - state.keycalm_last_pressed[key]
		if elapsed_time >= config.delay then
			state.keycalm_blocked[key] = false
			state.keycalm_counts[key] = 1 -- Restart counting from 1
			ya.notify({
				title = config.notify_title:gsub("{user}", os.getenv("USER") or "Cowboy"),
				content = config.notify_unblock:gsub("{key}", key),
				level = "info",
				timeout = config.delay,
			})
		else
			return -- Ignore input if delay is not over
		end
	end

	-- Increment counter
	state.keycalm_counts[key] = (state.keycalm_counts[key] or 0) + 1
	state.keycalm_last_pressed[key] = ya.time()

	-- If limit is reached, block the key
	if state.keycalm_counts[key] >= config.limit then
		state.keycalm_blocked[key] = true
		state.keycalm_counts[key] = 0 -- Reset counter

		ya.notify({
			title = config.notify_title:gsub("{user}", os.getenv("USER") or "Cowboy"),
			content = config.notify_message,
			level = "error",
			timeout = config.delay,
		})

		-- Unblock after delay
		ya.timer(config.delay, function()
			state.keycalm_blocked[key] = false
			ya.notify({
				title = config.notify_title:gsub("{user}", os.getenv("USER") or "Cowboy"),
				content = config.notify_unblock:gsub("{key}", key),
				level = "info",
				timeout = config.delay,
			})
		end)
		return
	end

	-- Move cursor if the key is not blocked
	if key == "j" then
		ya.manager_emit("arrow", { 1 })
	elseif key == "k" then
		ya.manager_emit("arrow", { -1 })
	end
end

M.setup()

return M
