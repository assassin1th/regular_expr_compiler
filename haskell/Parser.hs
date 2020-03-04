module Parser where

import Lexer
import Data.Char

data AST = CatNode  AST AST
         | OrNode   AST AST
	 | StarNode AST
	 | PlusNode AST
	 | MbNode   AST
	 | Range    String
	 | Symbol   Char
    deriving (Show, Eq)

parse :: [Token] -> AST
parse = undefined
