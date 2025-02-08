local M = {}

function M:peek()
	local start, cache = os.clock(), ya.file_cache(self)
	if not cache or self:preload() ~= 1 then
		return
	end

	ya.sleep(math.max(0, PREVIEW.image_delay / 1000 + start - os.clock()))
	ya.image_show(cache, self.area)
	ya.preview_widgets(self, {})
end

function M:seek(units)
	local h = cx.active.current.hovered
	if h and h.url == self.file.url then
		ya.manager_emit("peek", {
			math.max(0, cx.active.preview.skip + units),
			only_if = self.file.url,
		})
	end
end

function M:preload()
	local percentage = 5 + self.skip
	if percentage > 95 then
		ya.manager_emit("peek", { 90, only_if = self.file.url, upper_bound = true })
		return 2
	end

	local cache = ya.file_cache(self)
	if not cache or fs.cha(cache) then
		return 1
	end

	-- Get the video duration in seconds
	local probe = Command("ffprobe"):args({
		"-i", tostring(self.file.url), "-show_entries", "format=duration", "-v", "quiet", "-of", "csv=p=0"
	}):stdout(Command.PIPED):output()

	-- Calculate second to take thumbnail
	local sec = tonumber(probe.stdout) * percentage / 100

	local child, code = Command("ffmpeg"):args({
		"-ss",
		-- Replace `,` with `.` to prevent locale issues where the decimal separator is `,`
		tostring(sec):gsub(",", "."),
		"-i",
		tostring(self.file.url),
		"-vf",
		"scale=" .. tostring(PREVIEW.max_width) .. ":-1",
		"-q:v",
		"6",
		"-frames:v",
		"1",
		"-f",
		"image2",
		tostring(cache),
	}):spawn()

	if not child then
		ya.err("spawn `ffmpeg` command returns " .. tostring(code))
		return 0
	end

	local status = child:wait()
	return status and status.success and 1 or 2
end

return M
