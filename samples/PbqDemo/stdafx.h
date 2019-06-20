#pragma once

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "Resource.h"
#include "base/base.h"
#include "shared/shared.h"
#include "duilib/UIlib.h"


#include <ShellAPI.h>

enum 
{
	RA_DEFWM_TRAY_ICON_SHOWTASK = WM_USER + 1000,
	WM_ONCLOSE
};