public class Solution
    {
        public IList<IList<int>> Combine(int n, int k)
        {
            IList<IList<int>> result = new List<IList<int>>();
            dfs(1, new List<int>());

            return result;

            void dfs(int num, List<int> list)
            {
                if (list.Count == k)
                {
                    result.Add(new List<int>(list));
                    return;
                }

                for(int next = num; next<=n; next++)
                {
                    list.Add(next);
                    dfs(next + 1, list);
                    list.RemoveAt(list.Count - 1);
                }
            }
        }
    }