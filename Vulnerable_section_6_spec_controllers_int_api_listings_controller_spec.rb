   render_views
 
   let(:community) { FactoryGirl.create(:community) }
  let(:listing) { FactoryGirl.create(:listing) }

  before(:each) do
    @request.host = "#{community.ident}.lvh.me"
    @request.env[:current_marketplace] = community
    user = create_admin_for(community)
    sign_in_for_spec(user)
  end
 
   describe "#update_working_time_slots" do
     it 'works' do
       expect(listing.working_time_slots.count).to eq 0
       listing_params = {
       expect(listing.working_time_slots.count).to eq 0
       working_time_slot = JSON.parse(response.body)["working_time_slots"].first
       expect(working_time_slot["errors"]).to eq({
        "from" => ["\"Start time\" must be less than \"End time\""], "till"=>["\"Start time\" must be less than \"End time\""]
      })
     end
   end
 
       FactoryGirl.create(:listing_blocked_date, listing_id: listing.id, blocked_at: '2020-01-01')
     end
 
     it 'works' do
       expect(listing.blocked_dates.count).to eq 0
       listing_params = {
       expect(listing.blocked_dates.count).to eq 1
     end
   end
 end