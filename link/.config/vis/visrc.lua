-- Copied from
-- /usr/share/vis/visrc.lua

-- load standard vis module, providing parts of the Lua API
require('vis')

vis.events.subscribe(vis.events.INIT, function()
	-- Your global configuration options

	-- save my left pinky
	vis:map(vis.modes.NORMAL, " ", ":")
end)

vis.events.subscribe(vis.events.WIN_OPEN, function(win) -- luacheck: no unused args
	-- Your per window configuration options e.g.
	-- vis:command('set number')

	vis:command('set autoindent on')
	vis:command('set number')
	vis:command('set show-eof off')
	vis:command('set show-tabs on')
	vis:command('set tabwidth 4')
	vis:command('set theme dark-16')
end)
