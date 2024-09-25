# Notes

## Failing Sets

### Sets with Invalid Words

`television series that` -> `televisionseriesthat` -> `televisions er i est hat`
`game systems` -> `gamesystems` -> `games y stems`
`of the war` -> `ofthewar` -> `oft hew a r`
`a modern` -> `amodern` -> `am ode rn`

### Sets without Invalid Words

`of the` -> `ofthe` -> `oft he`
`in their` -> `intheir` -> `int heir`
`see the` -> `seethe` -> `seethe`
`is a stub` -> `isastub` -> `is as tub`

## Words to Add

Countries (American, Lithuanian, Austrian...)
Months (October, December, ...)

## General Flaws

If `word[i]` and `word[i+1]` successfully concatenate to a valid word, they will be treated as that combined valid word. Example: `see the` -> `seethe`. This likely can't be solved without grammatical analysis.

## Ideas

For something like `a modern` -> `amodern` -> `am ode rn`, we could consider the problem `p` to be `rn`. We could start with `TOTAL_TERMS=2` and try to reallocate the one space between `p` and it's neighbors within `distance 1`. Upon that failing, we could set `TOTAL_TERMS=2` and try to reallocate the 1-2 spaces between all neighbors within `distance 2`. Etc.
