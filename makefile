#Constant definitions

CC = gcc
CFLAGSR = -Wall
CFLAGSD = -g $(CFLAGSR)
OFLAGSR = -c $(CFLAGSR)
OFLAGSD = -c $(CFLAGSD)
IPATH = -ISource/Header

#Path to diferent modules

Binaries = bin
Sources = Source
Headers = Source/Header

#default make file, makes the full application


#Subordinate objects of the application Overwatch for Debug



#Subordinate objects of the application Overwatch for realease 


#Abreviated command


#Run the program

Run: 
	@$(Binaries)/*.app

Debug: $(Binaries)/
	@gdb $(Binaries)/

clean: 
	@rm -f $(Binaries)/*.o
	@rm -f $(Binaries)/*.app
