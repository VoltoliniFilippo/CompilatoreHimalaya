/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "scripts/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#define YYSTYPE Pnode
extern char *yytext;
extern int line;
extern Value lexval;
extern FILE *yyin;
int yylex();
Pnode root = NULL;

#line 85 "output/parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TYPE = 3,                       /* TYPE  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_BOOLEAN = 5,                    /* BOOLEAN  */
  YYSYMBOL_INTEGER = 6,                    /* INTEGER  */
  YYSYMBOL_REAL = 7,                       /* REAL  */
  YYSYMBOL_STRING = 8,                     /* STRING  */
  YYSYMBOL_VAR = 9,                        /* VAR  */
  YYSYMBOL_FUNC_P = 10,                    /* FUNC_P  */
  YYSYMBOL_END = 11,                       /* END  */
  YYSYMBOL_AND = 12,                       /* AND  */
  YYSYMBOL_OR = 13,                        /* OR  */
  YYSYMBOL_EQUAL = 14,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 15,                 /* NOT_EQUAL  */
  YYSYMBOL_GREATER = 16,                   /* GREATER  */
  YYSYMBOL_GREATER_EQUAL = 17,             /* GREATER_EQUAL  */
  YYSYMBOL_LESS = 18,                      /* LESS  */
  YYSYMBOL_LESS_EQUAL = 19,                /* LESS_EQUAL  */
  YYSYMBOL_IN = 20,                        /* IN  */
  YYSYMBOL_PLUS = 21,                      /* PLUS  */
  YYSYMBOL_MINUS = 22,                     /* MINUS  */
  YYSYMBOL_CONCAT = 23,                    /* CONCAT  */
  YYSYMBOL_TIMES = 24,                     /* TIMES  */
  YYSYMBOL_DIVIDE = 25,                    /* DIVIDE  */
  YYSYMBOL_NOT = 26,                       /* NOT  */
  YYSYMBOL_EMPTY = 27,                     /* EMPTY  */
  YYSYMBOL_HEAD_P = 28,                    /* HEAD_P  */
  YYSYMBOL_TAIL_P = 29,                    /* TAIL_P  */
  YYSYMBOL_BOOLCONST = 30,                 /* BOOLCONST  */
  YYSYMBOL_INTCONST = 31,                  /* INTCONST  */
  YYSYMBOL_REALCONST = 32,                 /* REALCONST  */
  YYSYMBOL_STRCONST = 33,                  /* STRCONST  */
  YYSYMBOL_IF = 34,                        /* IF  */
  YYSYMBOL_THEN = 35,                      /* THEN  */
  YYSYMBOL_ELSE = 36,                      /* ELSE  */
  YYSYMBOL_BODY = 37,                      /* BODY  */
  YYSYMBOL_READ_P = 38,                    /* READ_P  */
  YYSYMBOL_ELSIF = 39,                     /* ELSIF  */
  YYSYMBOL_WHILE = 40,                     /* WHILE  */
  YYSYMBOL_DO = 41,                        /* DO  */
  YYSYMBOL_FOR = 42,                       /* FOR  */
  YYSYMBOL_TO = 43,                        /* TO  */
  YYSYMBOL_WRITE = 44,                     /* WRITE  */
  YYSYMBOL_WRITELN = 45,                   /* WRITELN  */
  YYSYMBOL_COMMA = 46,                     /* COMMA  */
  YYSYMBOL_COLON = 47,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 48,                 /* SEMICOLON  */
  YYSYMBOL_ASSIGN = 49,                    /* ASSIGN  */
  YYSYMBOL_MOD = 50,                       /* MOD  */
  YYSYMBOL_RANGE = 51,                     /* RANGE  */
  YYSYMBOL_DOT = 52,                       /* DOT  */
  YYSYMBOL_LBRACE = 53,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 54,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 55,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 56,                  /* RBRACKET  */
  YYSYMBOL_LPARENTESIS = 57,               /* LPARENTESIS  */
  YYSYMBOL_RPARENTESIS = 58,               /* RPARENTESIS  */
  YYSYMBOL_YYACCEPT = 59,                  /* $accept  */
  YYSYMBOL_program = 60,                   /* program  */
  YYSYMBOL_type_section = 61,              /* type_section  */
  YYSYMBOL_type_decl_list = 62,            /* type_decl_list  */
  YYSYMBOL_type_decl = 63,                 /* type_decl  */
  YYSYMBOL_id_list = 64,                   /* id_list  */
  YYSYMBOL_65_1 = 65,                      /* @1  */
  YYSYMBOL_type = 66,                      /* type  */
  YYSYMBOL_atomic_type = 67,               /* atomic_type  */
  YYSYMBOL_struct_type = 68,               /* struct_type  */
  YYSYMBOL_atomic_decl_list = 69,          /* atomic_decl_list  */
  YYSYMBOL_atomic_decl = 70,               /* atomic_decl  */
  YYSYMBOL_71_2 = 71,                      /* @2  */
  YYSYMBOL_vector_type = 72,               /* vector_type  */
  YYSYMBOL_vector_elem_type = 73,          /* vector_elem_type  */
  YYSYMBOL_var_section = 74,               /* var_section  */
  YYSYMBOL_var_decl_list = 75,             /* var_decl_list  */
  YYSYMBOL_var_decl = 76,                  /* var_decl  */
  YYSYMBOL_func_section = 77,              /* func_section  */
  YYSYMBOL_func_decl_list = 78,            /* func_decl_list  */
  YYSYMBOL_func_decl = 79,                 /* func_decl  */
  YYSYMBOL_80_3 = 80,                      /* @3  */
  YYSYMBOL_opt_formal_decl_list = 81,      /* opt_formal_decl_list  */
  YYSYMBOL_formal_decl_list = 82,          /* formal_decl_list  */
  YYSYMBOL_formal_decl = 83,               /* formal_decl  */
  YYSYMBOL_84_4 = 84,                      /* @4  */
  YYSYMBOL_expr = 85,                      /* expr  */
  YYSYMBOL_bool_op = 86,                   /* bool_op  */
  YYSYMBOL_bool_term = 87,                 /* bool_term  */
  YYSYMBOL_comp_op = 88,                   /* comp_op  */
  YYSYMBOL_comp_term = 89,                 /* comp_term  */
  YYSYMBOL_add_op = 90,                    /* add_op  */
  YYSYMBOL_term = 91,                      /* term  */
  YYSYMBOL_mul_op = 92,                    /* mul_op  */
  YYSYMBOL_factor = 93,                    /* factor  */
  YYSYMBOL_unary_op = 94,                  /* unary_op  */
  YYSYMBOL_built_in = 95,                  /* built_in  */
  YYSYMBOL_atomic_constant = 96,           /* atomic_constant  */
  YYSYMBOL_struct_constructor = 97,        /* struct_constructor  */
  YYSYMBOL_expr_list = 98,                 /* expr_list  */
  YYSYMBOL_cond_expr = 99,                 /* cond_expr  */
  YYSYMBOL_func_call = 100,                /* func_call  */
  YYSYMBOL_101_5 = 101,                    /* @5  */
  YYSYMBOL_opt_expr_list = 102,            /* opt_expr_list  */
  YYSYMBOL_vector_constructor = 103,       /* vector_constructor  */
  YYSYMBOL_range = 104,                    /* range  */
  YYSYMBOL_body_section = 105,             /* body_section  */
  YYSYMBOL_stat_list = 106,                /* stat_list  */
  YYSYMBOL_stat = 107,                     /* stat  */
  YYSYMBOL_read_stat = 108,                /* read_stat  */
  YYSYMBOL_write_stat = 109,               /* write_stat  */
  YYSYMBOL_write_op = 110,                 /* write_op  */
  YYSYMBOL_assign_stat = 111,              /* assign_stat  */
  YYSYMBOL_lhs = 112,                      /* lhs  */
  YYSYMBOL_113_6 = 113,                    /* @6  */
  YYSYMBOL_opt_fielding = 114,             /* opt_fielding  */
  YYSYMBOL_indexing = 115,                 /* indexing  */
  YYSYMBOL_116_7 = 116,                    /* @7  */
  YYSYMBOL_if_stat = 117,                  /* if_stat  */
  YYSYMBOL_opt_elsif_stat_list = 118,      /* opt_elsif_stat_list  */
  YYSYMBOL_opt_else_stat = 119,            /* opt_else_stat  */
  YYSYMBOL_while_stat = 120,               /* while_stat  */
  YYSYMBOL_for_stat = 121,                 /* for_stat  */
  YYSYMBOL_122_8 = 122                     /* @8  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   208

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  64
/* YYNRULES -- Number of rules.  */
#define YYNRULES  126
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  214

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   313


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    22,    22,    32,    33,    36,    37,    40,    43,    43,
      44,    47,    48,    49,    52,    53,    54,    55,    56,    59,
      62,    63,    66,    66,    69,    72,    73,    76,    77,    80,
      81,    84,    87,    88,    92,    93,    96,    96,    99,   100,
     103,   104,   107,   107,   110,   111,   114,   115,   118,   119,
     122,   123,   124,   125,   126,   127,   128,   131,   132,   135,
     136,   137,   140,   141,   144,   145,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   161,   162,   165,
     166,   167,   168,   169,   172,   173,   174,   175,   178,   181,
     182,   185,   188,   188,   191,   192,   195,   198,   201,   204,
     205,   208,   209,   210,   211,   212,   213,   216,   219,   222,
     223,   226,   229,   229,   230,   233,   234,   237,   237,   240,
     243,   244,   247,   248,   251,   254,   254
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TYPE", "ID",
  "BOOLEAN", "INTEGER", "REAL", "STRING", "VAR", "FUNC_P", "END", "AND",
  "OR", "EQUAL", "NOT_EQUAL", "GREATER", "GREATER_EQUAL", "LESS",
  "LESS_EQUAL", "IN", "PLUS", "MINUS", "CONCAT", "TIMES", "DIVIDE", "NOT",
  "EMPTY", "HEAD_P", "TAIL_P", "BOOLCONST", "INTCONST", "REALCONST",
  "STRCONST", "IF", "THEN", "ELSE", "BODY", "READ_P", "ELSIF", "WHILE",
  "DO", "FOR", "TO", "WRITE", "WRITELN", "COMMA", "COLON", "SEMICOLON",
  "ASSIGN", "MOD", "RANGE", "DOT", "LBRACE", "RBRACE", "LBRACKET",
  "RBRACKET", "LPARENTESIS", "RPARENTESIS", "$accept", "program",
  "type_section", "type_decl_list", "type_decl", "id_list", "@1", "type",
  "atomic_type", "struct_type", "atomic_decl_list", "atomic_decl", "@2",
  "vector_type", "vector_elem_type", "var_section", "var_decl_list",
  "var_decl", "func_section", "func_decl_list", "func_decl", "@3",
  "opt_formal_decl_list", "formal_decl_list", "formal_decl", "@4", "expr",
  "bool_op", "bool_term", "comp_op", "comp_term", "add_op", "term",
  "mul_op", "factor", "unary_op", "built_in", "atomic_constant",
  "struct_constructor", "expr_list", "cond_expr", "func_call", "@5",
  "opt_expr_list", "vector_constructor", "range", "body_section",
  "stat_list", "stat", "read_stat", "write_stat", "write_op",
  "assign_stat", "lhs", "@6", "opt_fielding", "indexing", "@7", "if_stat",
  "opt_elsif_stat_list", "opt_else_stat", "while_stat", "for_stat", "@8", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-106)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-118)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,    11,    21,    15,    -6,  -106,    11,    -1,  -106,    11,
      56,    23,  -106,    12,    24,  -106,    11,    69,    44,    11,
    -106,  -106,  -106,  -106,  -106,    82,    71,    41,  -106,  -106,
    -106,    12,  -106,  -106,  -106,    69,    50,  -106,  -106,  -106,
      42,    55,  -106,  -106,    59,  -106,    75,    60,  -106,    85,
       3,   126,     3,   137,  -106,  -106,   134,    99,  -106,  -106,
       3,  -106,   117,  -106,  -106,  -106,  -106,   101,  -106,    82,
    -106,  -106,   169,   123,   124,     0,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,     3,     3,     3,
       3,     3,    96,  -106,   138,    88,  -106,     3,   125,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,    91,  -106,  -106,
      50,    49,     3,   164,  -106,  -106,   122,  -106,   135,   179,
    -106,     3,   127,   107,    33,    39,   131,    87,  -106,   130,
       1,  -106,  -106,    50,     3,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,     3,     3,  -106,  -106,     3,
    -106,     3,    50,   139,  -106,    49,  -106,   140,   142,   169,
    -106,    14,     3,     3,  -106,     3,  -106,     3,  -106,  -106,
     151,  -106,   104,    88,  -106,    10,   180,     3,    12,    12,
    -106,   123,   136,    98,  -106,    31,     3,   156,  -106,  -106,
      37,  -106,     3,  -106,  -106,     3,  -106,   109,    50,   182,
       3,   152,   165,    50,  -106,  -106,    94,  -106,  -106,   151,
      50,  -106,   184,  -106
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,    28,    10,     3,     6,     0,     1,     0,
      33,     0,     5,     0,     0,    27,    30,     0,     0,     0,
      18,    14,    15,    16,    17,     0,     0,     0,    11,    12,
      13,     0,    29,    36,    32,    35,     0,     2,     9,    22,
       0,    21,    25,    26,     0,     7,     0,     0,    34,   112,
       0,     0,     0,     0,   109,   110,     0,     0,   101,   102,
       0,   103,     0,   114,   104,   105,   106,     0,    19,     0,
      24,    31,    39,   116,     0,   112,    79,    80,    77,    78,
      81,    82,    83,    84,    85,    86,    87,     0,     0,     0,
      95,     0,     0,    45,    49,    58,    63,     0,     0,    71,
      72,    75,    76,    73,    74,    69,   107,     0,   125,    98,
     100,   108,     0,     0,    20,    42,     0,    38,    41,     0,
     113,     0,     0,     0,     0,    90,     0,    90,    94,     0,
       0,    46,    47,     0,     0,    50,    51,    52,    53,    54,
      55,    56,    59,    60,    61,     0,     0,    64,    65,     0,
      66,     0,     0,     0,    99,   111,    23,     0,     0,     0,
     115,     0,    95,     0,    68,     0,    88,     0,    96,    67,
     121,    44,    48,    57,    62,     0,     0,     0,     0,     0,
      40,   116,     0,     0,    89,     0,     0,   123,    70,   124,
       0,    43,     0,   118,    93,     0,    97,     0,     0,     0,
       0,     0,     0,     0,   122,   119,     0,    37,    91,   121,
       0,   120,     0,   126
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -106,  -106,  -106,   190,  -106,   120,  -106,   -29,   -22,   171,
     129,  -106,  -106,  -106,  -106,  -106,   183,  -106,  -106,   166,
    -106,  -106,  -106,    43,  -106,  -106,   -49,  -106,    66,  -106,
      58,  -106,    61,  -106,   -85,  -106,  -106,  -106,  -106,   -83,
    -106,  -106,  -106,    46,  -106,  -106,  -106,  -105,  -106,  -106,
    -106,  -106,  -106,   -36,  -106,    25,  -106,  -106,  -106,    -5,
    -106,  -106,  -106,  -106
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     5,     6,     7,    11,    27,    28,    29,
      40,    41,    67,    30,    44,    10,    15,    16,    18,    34,
      35,    47,   116,   117,   118,   157,   125,   134,    93,   145,
      94,   146,    95,   149,    96,    97,    98,    99,   100,   128,
     101,   102,   122,   129,   103,   104,    37,    56,    57,    58,
      59,    60,    61,   105,    73,   120,    63,    74,    64,   187,
     199,    65,    66,   153
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      62,    92,    46,   107,    42,   154,   126,    75,     1,    76,
      77,   111,   150,   131,   132,     4,    20,    21,    22,    23,
      24,     8,   131,   132,     9,    78,   131,   132,   170,    79,
      80,    81,    82,    83,    84,    85,    86,    87,   123,   124,
      -8,   127,   130,   131,   132,   131,   132,   176,    13,   131,
     132,   131,   132,    88,    49,  -117,    89,   -92,    90,   169,
      91,   131,   132,   155,   174,    25,    17,    26,   188,    19,
     181,    31,   161,    33,    62,    20,    21,    22,    23,    24,
     200,    36,   184,   164,    50,   165,    39,   196,    51,    45,
      52,   156,    53,   204,    54,    55,    68,    62,   209,   131,
     132,    69,   175,   131,   132,   212,   131,   132,   131,   132,
     131,   132,   147,   148,   183,    70,    62,    72,   185,   131,
     132,   131,   132,    71,    25,   142,   143,   144,   190,    14,
     106,   133,   152,   165,   195,   210,    14,   197,   167,    38,
    -117,   108,   163,   201,   203,   109,   202,   110,   113,   191,
     192,   206,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,    62,   207,   131,   132,   112,    62,    20,    21,
      22,    23,    24,   115,    62,   119,   208,   131,   132,   121,
     158,   159,   151,   160,   162,   166,   168,   178,   177,   179,
     186,   189,   198,   205,   194,   213,    12,    43,   114,    32,
     171,    48,   180,   172,   211,     0,   193,   173,   182
};

static const yytype_int16 yycheck[] =
{
      36,    50,    31,    52,    26,   110,    89,     4,     3,     6,
       7,    60,    97,    12,    13,     4,     4,     5,     6,     7,
       8,     0,    12,    13,     9,    22,    12,    13,   133,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    87,    88,
      46,    90,    91,    12,    13,    12,    13,   152,    49,    12,
      13,    12,    13,    50,     4,    55,    53,    57,    55,    58,
      57,    12,    13,   112,   149,    53,    10,    55,    58,    46,
      56,    47,   121,     4,   110,     4,     5,     6,     7,     8,
      43,    37,   165,    50,    34,    46,     4,    56,    38,    48,
      40,   113,    42,   198,    44,    45,    54,   133,   203,    12,
      13,    46,   151,    12,    13,   210,    12,    13,    12,    13,
      12,    13,    24,    25,   163,    56,   152,    57,   167,    12,
      13,    12,    13,    48,    53,    21,    22,    23,   177,     9,
       4,    35,    41,    46,    36,    41,    16,   186,    51,    19,
      55,     4,    35,   192,    35,    11,   195,    48,    47,   178,
     179,   200,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,   198,    11,    12,    13,    49,   203,     4,     5,
       6,     7,     8,     4,   210,    52,    11,    12,    13,    55,
      58,    46,    57,     4,    57,    54,    56,    47,    49,    47,
      39,    11,    36,    11,    58,    11,     6,    26,    69,    16,
     134,    35,   159,   145,   209,    -1,   181,   146,   162
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    60,    61,     4,    62,    63,    64,     0,     9,
      74,    65,    62,    49,    64,    75,    76,    10,    77,    46,
       4,     5,     6,     7,     8,    53,    55,    66,    67,    68,
      72,    47,    75,     4,    78,    79,    37,   105,    64,     4,
      69,    70,    67,    68,    73,    48,    66,    80,    78,     4,
      34,    38,    40,    42,    44,    45,   106,   107,   108,   109,
     110,   111,   112,   115,   117,   120,   121,    71,    54,    46,
      56,    48,    57,   113,   116,     4,     6,     7,    22,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    50,    53,
      55,    57,    85,    87,    89,    91,    93,    94,    95,    96,
      97,    99,   100,   103,   104,   112,     4,    85,     4,    11,
      48,    85,    49,    47,    69,     4,    81,    82,    83,    52,
     114,    55,   101,    85,    85,    85,    98,    85,    98,   102,
      85,    12,    13,    35,    86,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    88,    90,    24,    25,    92,
      93,    57,    41,   122,   106,    85,    67,    84,    58,    46,
       4,    85,    57,    35,    50,    46,    54,    51,    56,    58,
     106,    87,    89,    91,    93,    85,   106,    49,    47,    47,
      82,    56,   102,    85,    98,    85,    39,   118,    58,    11,
      85,    66,    66,   114,    58,    36,    56,    85,    36,   119,
      43,    85,    85,    35,   106,    11,    85,    11,    11,   106,
      41,   118,   106,    11
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    60,    61,    61,    62,    62,    63,    65,    64,
      64,    66,    66,    66,    67,    67,    67,    67,    67,    68,
      69,    69,    71,    70,    72,    73,    73,    74,    74,    75,
      75,    76,    77,    77,    78,    78,    80,    79,    81,    81,
      82,    82,    84,    83,    85,    85,    86,    86,    87,    87,
      88,    88,    88,    88,    88,    88,    88,    89,    89,    90,
      90,    90,    91,    91,    92,    92,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    94,    94,    95,
      95,    95,    95,    95,    96,    96,    96,    96,    97,    98,
      98,    99,   101,   100,   102,   102,   103,   104,   105,   106,
     106,   107,   107,   107,   107,   107,   107,   108,   109,   110,
     110,   111,   113,   112,   112,   114,   114,   116,   115,   117,
     118,   118,   119,   119,   120,   122,   121
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     2,     0,     2,     1,     4,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     0,     4,     3,     1,     1,     2,     0,     2,
       1,     4,     2,     0,     2,     1,     0,     9,     1,     0,
       3,     1,     0,     4,     3,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     3,     1,     1,     1,     2,     3,     3,     1,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       1,     7,     0,     5,     1,     0,     3,     5,     3,     3,
       2,     1,     1,     1,     1,     1,     1,     2,     2,     1,
       1,     3,     0,     3,     1,     2,     0,     0,     6,     7,
       5,     0,     2,     0,     5,     0,    10
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: type_section var_section func_section body_section  */
#line 23 "scripts/parser.y"
        {
            root = yyval = newnode(N_PROGRAM);
            yyval->c1 = yyvsp[-3]; //type section
            yyval->c2 = yyvsp[-2]; //var section
            yyval->c3 = yyvsp[-1]; //func section
            yyval->c4 = yyvsp[0]; //body section
        }
#line 1362 "output/parser.c"
    break;

  case 3: /* type_section: TYPE type_decl_list  */
#line 32 "scripts/parser.y"
                                  {yyval = yyvsp[0];}
#line 1368 "output/parser.c"
    break;

  case 4: /* type_section: %empty  */
#line 33 "scripts/parser.y"
              {yyval = NULL;}
#line 1374 "output/parser.c"
    break;

  case 5: /* type_decl_list: type_decl type_decl_list  */
#line 36 "scripts/parser.y"
                                         {yyval = yyvsp[-1]; yyval->b = yyvsp[0];}
#line 1380 "output/parser.c"
    break;

  case 6: /* type_decl_list: type_decl  */
#line 37 "scripts/parser.y"
                          {yyval = yyvsp[0];}
#line 1386 "output/parser.c"
    break;

  case 7: /* type_decl: id_list ASSIGN type SEMICOLON  */
#line 40 "scripts/parser.y"
                                         {yyval = newnode(N_TYPE_DECL); yyval->c1 = yyvsp[-3]; yyval->c2 = yyvsp[-1];}
#line 1392 "output/parser.c"
    break;

  case 8: /* @1: %empty  */
#line 43 "scripts/parser.y"
            {yyval = idnode();}
#line 1398 "output/parser.c"
    break;

  case 9: /* id_list: ID @1 COMMA id_list  */
#line 43 "scripts/parser.y"
                                           {yyval = yyvsp[-2]; yyvsp[-2]->b = yyvsp[0];}
#line 1404 "output/parser.c"
    break;

  case 10: /* id_list: ID  */
#line 44 "scripts/parser.y"
             {yyval = idnode();}
#line 1410 "output/parser.c"
    break;

  case 14: /* atomic_type: BOOLEAN  */
#line 52 "scripts/parser.y"
                      {yyval = newnode(T_BOOLEAN);}
#line 1416 "output/parser.c"
    break;

  case 15: /* atomic_type: INTEGER  */
#line 53 "scripts/parser.y"
                      {yyval = newnode(T_INTEGER);}
#line 1422 "output/parser.c"
    break;

  case 16: /* atomic_type: REAL  */
#line 54 "scripts/parser.y"
                   {yyval = newnode(T_REAL);}
#line 1428 "output/parser.c"
    break;

  case 17: /* atomic_type: STRING  */
#line 55 "scripts/parser.y"
                     {yyval = newnode(T_STRING);}
#line 1434 "output/parser.c"
    break;

  case 18: /* atomic_type: ID  */
#line 56 "scripts/parser.y"
                 {yyval = idnode();}
#line 1440 "output/parser.c"
    break;

  case 19: /* struct_type: LBRACE atomic_decl_list RBRACE  */
#line 59 "scripts/parser.y"
                                            {yyval = newnode(N_STRUCT_TYPE); yyval->c1 = yyvsp[-1];}
#line 1446 "output/parser.c"
    break;

  case 20: /* atomic_decl_list: atomic_decl COMMA atomic_decl_list  */
#line 62 "scripts/parser.y"
                                                     {yyval = yyvsp[-2]; yyval->b = yyvsp[0];}
#line 1452 "output/parser.c"
    break;

  case 21: /* atomic_decl_list: atomic_decl  */
#line 63 "scripts/parser.y"
                               {yyval = yyvsp[0];}
#line 1458 "output/parser.c"
    break;

  case 22: /* @2: %empty  */
#line 66 "scripts/parser.y"
                {yyval = idnode();}
#line 1464 "output/parser.c"
    break;

  case 23: /* atomic_decl: ID @2 COLON atomic_type  */
#line 66 "scripts/parser.y"
                                                   {yyval = newnode(N_ATOMIC_DECL); yyval->c1 = yyvsp[-2]; yyval->c2 = yyvsp[0];}
#line 1470 "output/parser.c"
    break;

  case 24: /* vector_type: LBRACKET vector_elem_type RBRACKET  */
#line 69 "scripts/parser.y"
                                                {yyval = newnode(N_VECTOR_TYPE);yyval->c1 = yyvsp[-1];}
#line 1476 "output/parser.c"
    break;

  case 27: /* var_section: VAR var_decl_list  */
#line 76 "scripts/parser.y"
                               {yyval = yyvsp[0];}
#line 1482 "output/parser.c"
    break;

  case 28: /* var_section: %empty  */
#line 77 "scripts/parser.y"
             {yyval = NULL;}
#line 1488 "output/parser.c"
    break;

  case 29: /* var_decl_list: var_decl var_decl_list  */
#line 80 "scripts/parser.y"
                                      {yyval = yyvsp[-1]; yyval->b = yyvsp[0];}
#line 1494 "output/parser.c"
    break;

  case 31: /* var_decl: id_list COLON type SEMICOLON  */
#line 84 "scripts/parser.y"
                                       {yyval = newnode(N_VAR_DECL); yyval->c1 = yyvsp[-3]; yyval->c2 = yyvsp[-1];}
#line 1500 "output/parser.c"
    break;

  case 32: /* func_section: FUNC_P func_decl_list  */
#line 87 "scripts/parser.y"
                                    {yyval = yyvsp[0];}
#line 1506 "output/parser.c"
    break;

  case 33: /* func_section: %empty  */
#line 88 "scripts/parser.y"
              {yyval = NULL;}
#line 1512 "output/parser.c"
    break;

  case 34: /* func_decl_list: func_decl func_decl_list  */
#line 92 "scripts/parser.y"
                                         {yyval = yyvsp[-1]; yyvsp[-1]->b = yyvsp[0];}
#line 1518 "output/parser.c"
    break;

  case 35: /* func_decl_list: func_decl  */
#line 93 "scripts/parser.y"
                          {yyval = yyvsp[0];}
#line 1524 "output/parser.c"
    break;

  case 36: /* @3: %empty  */
#line 96 "scripts/parser.y"
              {yyval = newnode(N_FUNC_DECL); yyval->value.sval = lexval.sval;}
#line 1530 "output/parser.c"
    break;

  case 37: /* func_decl: ID @3 LPARENTESIS opt_formal_decl_list RPARENTESIS COLON type expr END  */
#line 96 "scripts/parser.y"
                                                                                                                                          {yyval = yyvsp[-7]; yyval->c1 = yyvsp[-5]; yyval->c2 = yyvsp[-2]; yyval->c3 = yyvsp[-1];}
#line 1536 "output/parser.c"
    break;

  case 38: /* opt_formal_decl_list: formal_decl_list  */
#line 99 "scripts/parser.y"
                                       {yyval = yyvsp[0];}
#line 1542 "output/parser.c"
    break;

  case 39: /* opt_formal_decl_list: %empty  */
#line 100 "scripts/parser.y"
                       {yyval = NULL;}
#line 1548 "output/parser.c"
    break;

  case 40: /* formal_decl_list: formal_decl COMMA formal_decl_list  */
#line 103 "scripts/parser.y"
                                                     {yyval = yyvsp[-2]; yyvsp[-2]->b = yyvsp[0];}
#line 1554 "output/parser.c"
    break;

  case 42: /* @4: %empty  */
#line 107 "scripts/parser.y"
                {yyval = idnode();}
#line 1560 "output/parser.c"
    break;

  case 43: /* formal_decl: ID @4 COLON type  */
#line 107 "scripts/parser.y"
                                            {yyval = yyvsp[-2]; yyvsp[-2]->c1 = yyvsp[0];}
#line 1566 "output/parser.c"
    break;

  case 44: /* expr: expr bool_op bool_term  */
#line 110 "scripts/parser.y"
                             {yyval = yyvsp[-1]; yyval->c1 = yyvsp[-2]; yyval->c2 = yyvsp[0];}
#line 1572 "output/parser.c"
    break;

  case 46: /* bool_op: AND  */
#line 114 "scripts/parser.y"
             {yyval = newnode(N_LOGIC_EXPR); yyval->value.ival = VAL_AND;}
#line 1578 "output/parser.c"
    break;

  case 47: /* bool_op: OR  */
#line 115 "scripts/parser.y"
            {yyval = newnode(N_LOGIC_EXPR); yyval->value.ival = VAL_OR;}
#line 1584 "output/parser.c"
    break;

  case 48: /* bool_term: comp_term comp_op comp_term  */
#line 118 "scripts/parser.y"
                                       {yyval = yyvsp[-1]; yyval->c1 = yyvsp[-2]; yyval->c2 = yyvsp[0];}
#line 1590 "output/parser.c"
    break;

  case 50: /* comp_op: EQUAL  */
#line 122 "scripts/parser.y"
               {yyval = newnode(N_COMP_EXPR); yyval->value.ival = VAL_EQ;}
#line 1596 "output/parser.c"
    break;

  case 51: /* comp_op: NOT_EQUAL  */
#line 123 "scripts/parser.y"
                   {yyval = newnode(N_COMP_EXPR); yyval->value.ival = VAL_NE;}
#line 1602 "output/parser.c"
    break;

  case 52: /* comp_op: GREATER  */
#line 124 "scripts/parser.y"
                 {yyval = newnode(N_COMP_EXPR); yyval->value.ival = VAL_GT;}
#line 1608 "output/parser.c"
    break;

  case 53: /* comp_op: GREATER_EQUAL  */
#line 125 "scripts/parser.y"
                       {yyval = newnode(N_COMP_EXPR); yyval->value.ival = VAL_GE;}
#line 1614 "output/parser.c"
    break;

  case 54: /* comp_op: LESS  */
#line 126 "scripts/parser.y"
              {yyval = newnode(N_COMP_EXPR); yyval->value.ival = VAL_LT;}
#line 1620 "output/parser.c"
    break;

  case 55: /* comp_op: LESS_EQUAL  */
#line 127 "scripts/parser.y"
                    {yyval = newnode(N_COMP_EXPR); yyval->value.ival = VAL_LE;}
#line 1626 "output/parser.c"
    break;

  case 56: /* comp_op: IN  */
#line 128 "scripts/parser.y"
            {yyval = newnode(N_COMP_EXPR); yyval->value.ival = VAL_IN;}
#line 1632 "output/parser.c"
    break;

  case 57: /* comp_term: comp_term add_op term  */
#line 131 "scripts/parser.y"
                                 {yyval = yyvsp[-1]; yyval->c1 = yyvsp[-2]; yyval->c2 = yyvsp[0];}
#line 1638 "output/parser.c"
    break;

  case 59: /* add_op: PLUS  */
#line 135 "scripts/parser.y"
             {yyval = newnode(N_MATH_EXPR); yyval->value.ival = VAL_PLUS;}
#line 1644 "output/parser.c"
    break;

  case 60: /* add_op: MINUS  */
#line 136 "scripts/parser.y"
              {yyval = newnode(N_MATH_EXPR); yyval->value.ival = VAL_MINUS;}
#line 1650 "output/parser.c"
    break;

  case 61: /* add_op: CONCAT  */
#line 137 "scripts/parser.y"
               {yyval = newnode(N_MATH_EXPR); yyval->value.ival = VAL_PLUSPLUS;}
#line 1656 "output/parser.c"
    break;

  case 62: /* term: term mul_op factor  */
#line 140 "scripts/parser.y"
                         {yyval = yyvsp[-1]; yyval->c1 = yyvsp[-2]; yyval->c2 = yyvsp[0];}
#line 1662 "output/parser.c"
    break;

  case 64: /* mul_op: TIMES  */
#line 144 "scripts/parser.y"
              {yyval = newnode(N_MATH_EXPR); yyval->value.ival = VAL_TIMES;}
#line 1668 "output/parser.c"
    break;

  case 65: /* mul_op: DIVIDE  */
#line 145 "scripts/parser.y"
               {yyval = newnode(N_MATH_EXPR); yyval->value.ival = VAL_DIVIDE;}
#line 1674 "output/parser.c"
    break;

  case 66: /* factor: unary_op factor  */
#line 148 "scripts/parser.y"
                        {yyval = yyvsp[-1]; yyval->c1 = yyvsp[0];}
#line 1680 "output/parser.c"
    break;

  case 67: /* factor: LPARENTESIS expr RPARENTESIS  */
#line 149 "scripts/parser.y"
                                     {yyval = yyvsp[-1];}
#line 1686 "output/parser.c"
    break;

  case 68: /* factor: MOD expr MOD  */
#line 150 "scripts/parser.y"
                     {yyval = newnode(N_BUILT_IN_EXPR); yyval->value.ival = VAL_CARD; yyval->c1 = yyvsp[-1];}
#line 1692 "output/parser.c"
    break;

  case 70: /* factor: built_in LPARENTESIS expr RPARENTESIS  */
#line 152 "scripts/parser.y"
                                              {yyval = yyvsp[-3]; yyval->c1 = yyvsp[-1];}
#line 1698 "output/parser.c"
    break;

  case 77: /* unary_op: MINUS  */
#line 161 "scripts/parser.y"
                 {yyval = newnode(N_NEG_EXPR); yyval->value.ival = VAL_MINUS;}
#line 1704 "output/parser.c"
    break;

  case 78: /* unary_op: NOT  */
#line 162 "scripts/parser.y"
              {yyval = newnode(N_LOGIC_EXPR); yyval->value.ival = VAL_NOT;}
#line 1710 "output/parser.c"
    break;

  case 79: /* built_in: INTEGER  */
#line 165 "scripts/parser.y"
                  {yyval = newnode(N_BUILT_IN_EXPR); yyval->value.ival = VAL_INTEGER;}
#line 1716 "output/parser.c"
    break;

  case 80: /* built_in: REAL  */
#line 166 "scripts/parser.y"
               {yyval = newnode(N_BUILT_IN_EXPR); yyval->value.ival = VAL_REAL;}
#line 1722 "output/parser.c"
    break;

  case 81: /* built_in: EMPTY  */
#line 167 "scripts/parser.y"
                {yyval = newnode(N_BUILT_IN_EXPR); yyval->value.ival = VAL_EMPTY;}
#line 1728 "output/parser.c"
    break;

  case 82: /* built_in: HEAD_P  */
#line 168 "scripts/parser.y"
                 {yyval = newnode(N_BUILT_IN_EXPR); yyval->value.ival = VAL_HEAD;}
#line 1734 "output/parser.c"
    break;

  case 83: /* built_in: TAIL_P  */
#line 169 "scripts/parser.y"
                 {yyval = newnode(N_BUILT_IN_EXPR); yyval->value.ival = VAL_TAIL;}
#line 1740 "output/parser.c"
    break;

  case 84: /* atomic_constant: BOOLCONST  */
#line 172 "scripts/parser.y"
                           {yyval = boolconstnode();}
#line 1746 "output/parser.c"
    break;

  case 85: /* atomic_constant: INTCONST  */
#line 173 "scripts/parser.y"
                          {yyval = intconstnode();}
#line 1752 "output/parser.c"
    break;

  case 86: /* atomic_constant: REALCONST  */
#line 174 "scripts/parser.y"
                           {yyval = realconstnode();}
#line 1758 "output/parser.c"
    break;

  case 87: /* atomic_constant: STRCONST  */
#line 175 "scripts/parser.y"
                          {yyval = strconstnode();}
#line 1764 "output/parser.c"
    break;

  case 88: /* struct_constructor: LBRACE expr_list RBRACE  */
#line 178 "scripts/parser.y"
                                            {yyval = newnode(N_CONSTRUCTOR); yyval->value.ival = VAL_STRUCT; yyval->c1 = yyvsp[-1];}
#line 1770 "output/parser.c"
    break;

  case 89: /* expr_list: expr COMMA expr_list  */
#line 181 "scripts/parser.y"
                                {yyval = yyvsp[-2]; yyval->b = yyvsp[0];}
#line 1776 "output/parser.c"
    break;

  case 91: /* cond_expr: IF expr THEN expr ELSE expr END  */
#line 185 "scripts/parser.y"
                                           {yyval = newnode(N_COND_EXPR); yyval->c1 = yyvsp[-5]; yyval->c2 = yyvsp[-3]; yyval->c3 = yyvsp[-1];}
#line 1782 "output/parser.c"
    break;

  case 92: /* @5: %empty  */
#line 188 "scripts/parser.y"
              {yyval = newnode(N_FUNC_CALL); yyval->value.sval = lexval.sval;}
#line 1788 "output/parser.c"
    break;

  case 93: /* func_call: ID @5 LPARENTESIS opt_expr_list RPARENTESIS  */
#line 188 "scripts/parser.y"
                                                                                                               {yyval = yyvsp[-3]; yyval->c1 = yyvsp[-1];}
#line 1794 "output/parser.c"
    break;

  case 95: /* opt_expr_list: %empty  */
#line 192 "scripts/parser.y"
                {yyval = NULL;}
#line 1800 "output/parser.c"
    break;

  case 96: /* vector_constructor: LBRACKET opt_expr_list RBRACKET  */
#line 195 "scripts/parser.y"
                                                    {yyval = newnode(N_CONSTRUCTOR); yyval->value.ival = VAL_VECT; yyval->c1 = yyvsp[-1];}
#line 1806 "output/parser.c"
    break;

  case 97: /* range: LBRACKET expr RANGE expr RBRACKET  */
#line 198 "scripts/parser.y"
                                         {yyval = newnode(N_RANGE); yyval->c1 = yyvsp[-3]; yyval->c2 = yyvsp[-1];}
#line 1812 "output/parser.c"
    break;

  case 98: /* body_section: BODY stat_list END  */
#line 201 "scripts/parser.y"
                                 {yyval = yyvsp[-1];}
#line 1818 "output/parser.c"
    break;

  case 99: /* stat_list: stat SEMICOLON stat_list  */
#line 204 "scripts/parser.y"
                                    {yyval = yyvsp[-2]; yyvsp[-2]->b = yyvsp[0];}
#line 1824 "output/parser.c"
    break;

  case 100: /* stat_list: stat SEMICOLON  */
#line 205 "scripts/parser.y"
                          {yyval = yyvsp[-1];}
#line 1830 "output/parser.c"
    break;

  case 107: /* read_stat: READ_P ID  */
#line 216 "scripts/parser.y"
                     {yyval = newnode(N_READ_STAT); yyval->c1 = idnode();}
#line 1836 "output/parser.c"
    break;

  case 108: /* write_stat: write_op expr  */
#line 219 "scripts/parser.y"
                          {yyval = yyvsp[-1]; yyval->c1 = yyvsp[0];}
#line 1842 "output/parser.c"
    break;

  case 109: /* write_op: WRITE  */
#line 222 "scripts/parser.y"
                {yyval = newnode(N_WRITE_STAT); yyval->value.ival = VAL_WRITE;}
#line 1848 "output/parser.c"
    break;

  case 110: /* write_op: WRITELN  */
#line 223 "scripts/parser.y"
                  {yyval = newnode(N_WRITE_STAT); yyval->value.ival = VAL_WRITELN;}
#line 1854 "output/parser.c"
    break;

  case 111: /* assign_stat: lhs ASSIGN expr  */
#line 226 "scripts/parser.y"
                             {yyval = newnode(N_ASSIGN_STAT); yyval->c1 = yyvsp[-2]; yyval->c2 = yyvsp[0];}
#line 1860 "output/parser.c"
    break;

  case 112: /* @6: %empty  */
#line 229 "scripts/parser.y"
        {yyval = idnode();}
#line 1866 "output/parser.c"
    break;

  case 113: /* lhs: ID @6 opt_fielding  */
#line 229 "scripts/parser.y"
                                      {yyval = newnode(N_LHS); yyval->c1 = yyvsp[-1]; yyval->c2 = yyvsp[0];}
#line 1872 "output/parser.c"
    break;

  case 114: /* lhs: indexing  */
#line 230 "scripts/parser.y"
               {yyval = newnode(N_LHS); yyval->c1 = yyvsp[0];}
#line 1878 "output/parser.c"
    break;

  case 115: /* opt_fielding: DOT ID  */
#line 233 "scripts/parser.y"
                     {yyval = idnode();}
#line 1884 "output/parser.c"
    break;

  case 116: /* opt_fielding: %empty  */
#line 234 "scripts/parser.y"
              {yyval = NULL;}
#line 1890 "output/parser.c"
    break;

  case 117: /* @7: %empty  */
#line 237 "scripts/parser.y"
             {yyval = idnode();}
#line 1896 "output/parser.c"
    break;

  case 118: /* indexing: ID @7 LBRACKET expr RBRACKET opt_fielding  */
#line 237 "scripts/parser.y"
                                                                  {yyval = newnode(N_INDEXING); yyval->c1 = yyvsp[-4]; yyval->c2 = yyvsp[-2]; yyval->c3 = yyvsp[0];}
#line 1902 "output/parser.c"
    break;

  case 119: /* if_stat: IF expr THEN stat_list opt_elsif_stat_list opt_else_stat END  */
#line 240 "scripts/parser.y"
                                                                      {yyval = newnode(N_IF_STAT); yyval->c1 = yyvsp[-5]; yyval->c2 = yyvsp[-3]; yyval->c3 = yyvsp[-2]; yyval->c4 = yyvsp[-1];}
#line 1908 "output/parser.c"
    break;

  case 120: /* opt_elsif_stat_list: ELSIF expr THEN stat_list opt_elsif_stat_list  */
#line 243 "scripts/parser.y"
                                                                   {yyval = newnode(N_OPT_ELSIF_STAT_LIST); yyval->c1 = yyvsp[-3]; yyval->c2 = yyvsp[-1]; yyval->b = yyvsp[0];}
#line 1914 "output/parser.c"
    break;

  case 121: /* opt_elsif_stat_list: %empty  */
#line 244 "scripts/parser.y"
                       {yyval = NULL;}
#line 1920 "output/parser.c"
    break;

  case 122: /* opt_else_stat: ELSE stat_list  */
#line 247 "scripts/parser.y"
                              {yyval = yyvsp[0];}
#line 1926 "output/parser.c"
    break;

  case 123: /* opt_else_stat: %empty  */
#line 248 "scripts/parser.y"
               {yyval = NULL;}
#line 1932 "output/parser.c"
    break;

  case 124: /* while_stat: WHILE expr DO stat_list END  */
#line 251 "scripts/parser.y"
                                        {yyval = newnode(N_WHILE_STAT); yyval->c1 = yyvsp[-3]; yyval->c2 = yyvsp[-1];}
#line 1938 "output/parser.c"
    break;

  case 125: /* @8: %empty  */
#line 254 "scripts/parser.y"
                 {yyval = idnode();}
#line 1944 "output/parser.c"
    break;

  case 126: /* for_stat: FOR ID @8 ASSIGN expr TO expr DO stat_list END  */
#line 254 "scripts/parser.y"
                                                                       {yyval = newnode(N_FOR_STAT); yyval->c1 = yyvsp[-7]; yyval->c2 = yyvsp[-5]; yyval->c3 = yyvsp[-3]; yyval->c4 = yyvsp[-1];}
#line 1950 "output/parser.c"
    break;


#line 1954 "output/parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 257 "scripts/parser.y"

Pnode idnode()
{
    Pnode p = newnode(T_ID);
    p->value.sval = lexval.sval;
    return(p);
}

Pnode keynode(Symbol keyword)
{
    return newnode(keyword);
}

Pnode intconstnode(){
    Pnode p = newnode(T_INTCONST);
    p->value.ival = lexval.ival;
    return(p);
}

Pnode realconstnode()
{
    Pnode p = newnode(T_REALCONST);
    p->value.rval = lexval.rval;
    return(p);
}

Pnode strconstnode()
{
    Pnode p = newnode(T_STRCONST);
    p->value.sval = lexval.sval;
    return(p);
}

Pnode boolconstnode()
{
    Pnode p = newnode(T_BOOLCONST);
    p->value.ival = lexval.ival;
    return(p);
}

Pnode newnode(Symbol symbol)
{
    Pnode p = malloc(sizeof(Node));
    p->symbol = symbol;
    p->line = line;
    p->c1 = p->c2 = p->c3 = p->c4 = NULL;
    p->b = NULL;
    return p;
}

void yyerror()
{
    fprintf(stderr, "Line %d: syntax error on symbol \"%s\"\n",line, yytext);
    exit(-1);
}

Code *genCode(){
    static Code gencode;
    int result;

    if((result = yyparse() == 0))
        gencode = semantic_analysis(root);

    /*
    print_symbol_table();
    treeprint(root, 0);
    print_generated_code(gencode);
    */

    return &gencode;
}

/*void main(){
    static Code gencode;
    int result;

    if((result = yyparse() == 0))
        gencode = semantic_analysis(root);
    
    print_generated_code(gencode);
}*/
