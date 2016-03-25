
def ambiguous_base(n, base):
    ans = []
    def helper(total, rem, exp):
        if rem == 0:
            ans.append(total)
            return
        cut = 10
        while rem%cut < base and cut//10 <= rem:
            # Removing leading 0 issue
            if cut>10 and rem%cut == rem%(cut//10):
                cut *= 10
                continue
            helper(total + (rem%cut)*(base**exp), rem//cut, exp+1)
            cut *= 10
            continue

    helper(0, n, 0)
    return sorted(ans)

print(ambiguous_base(101, 2))
print(ambiguous_base(101, 16))
print(ambiguous_base(120973, 25))
print(ambiguous_base(25190239128039083901283, 100)[:10])
print(ambiguous_base(251902391280395901283, 2398)[:10])

