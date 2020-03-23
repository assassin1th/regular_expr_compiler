module AST where

import Data.Tree
import Data.List
import Control.Monad.Writer

data Op a = Cat
          | Operand a
    deriving (Show)

type AST a = Tree (Op a)

buildAST :: (Lexical a) => [a] -> AST a
buildAST = parse . unfoldr scan

data Token a = Meta a
             | Literal a

class Eq a => Lexical a where
    scan :: [a] -> Maybe (Token a, [a])

instance Lexical Char where
    scan []       = Nothing
    scan (x : xs) = Just (Literal x, xs)

parse :: [Token a] -> AST a
parse = fst . cat

cat :: [Token a] -> (AST a, [Token a])
cat = let iter (op, []) = (op, [])
          iter (op, xs) = let (op', xs') = operand xs
	                  in case xs of
	                     _ -> iter (Node Cat [op, op'], xs')
      in  iter . operand

operand :: [Token a] -> (AST a, [Token a])
operand []       = error "expected an operand"
operand (Literal x : xs) = (Node (Operand x) [], xs)
