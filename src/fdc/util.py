import pythoncom

def util_get_uuid():
	return str(pythoncom.CreateGuid()).strip('{}')