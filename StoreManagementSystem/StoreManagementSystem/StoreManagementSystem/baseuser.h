#pragma once

#ifndef  SMS_BASEUSER_H
#define SMS_BASEUSER_H

class BaseUser
{
	virtual bool logIn(char *fileName) = 0; // µÇÂ¼
	virtual void logOut() = 0; // µÇ³ö
};

#endif // ! SMS_BASEUSER_H
