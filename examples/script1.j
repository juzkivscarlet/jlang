#	examples/SCRIPT1.j
	.HEADER
.FILE		script1
.PROGRAM	test
.global		_start
.include	("defaults")
	;;	end .HEADER

############################################################
	.DATA
.SUBSECTION funcs
	_printf	func(input:str,	.optional vars:obj[]):bool
;	end .SUBSECTION funcs

.SUBSECTION structs
#	BIRTHDAY
	.struct	type _birthday ::
		.public year:int									\
		\	.must ((- >= 1900)	&& (- >= _TIME.now().year))
		\	.require

		month:int			.must ((- > 0)	&&	(- <= 12))
		.private date:int	.must ((- > 0)	&&	(- <= 31))

		month:int
		month_name:str		.setter ::
			if (-.month)
				-.month_name	= _months[month + 1]
		;

		- .method	print(null)
	;

	_birthday.print(null):void
		_printf ("\t%n %s, %n\n",						\
			\	[this.date, this.month_name, this.year])
	..
#		`..` = C: `return null;`

#	PERSON
	.struct type _person ::
		.public name:str[2]	.require
		.public	age:int
		bday:_birthday		.optional
	;
	
;	end .SUBSECTION structs

.SUBSECTION vars
	abc:char*[26]
	.public	(bar, foo):bool	= (true, false)
	.const	Pi:float32		= 3.1415926535

	(.const .public) _months:str[12]	.map [
		"january",
		"february",
		"march",
		"april",
		"may",
		"june",
		"july",
		"august",
		"september",
		"october",
		"november",
		"december",		# last comma will be ignored
	]
;	end .SUBSECTION vars
	;;	end .DATA

############################################################
	.CODE

#   _PRINTF("...", [...])
_printf	func(input:str, vars:obj[] .optional):bool ::
	if ((!input)	||	(_datatype(input) != str)) ::
		.. false;

	. true
;
	;;	end .CODE

# main function goes at the end
#   _START()
_start	func(argc:int, argv:str*[]):int ::
	let		john:_person
	john->name[1]	= "John"
	john->name[2]	= "Smith"
	john->age		= 25
	john->bday		= .new(_birthday, 1996, 2, 18)

	. 0
;

###########################################################
;;;	end .FILE script1

